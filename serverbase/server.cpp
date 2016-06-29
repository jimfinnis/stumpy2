/**
 * @file
 * Server implementation.
 * 
 */

#include "server.h"
#include "stdConns.h"
#include <ctype.h>

/// flag tells us to exit
static volatile int exit_request=0;
/// signal handler
static void serv_hdl(int sig){
    if(sig == SIGTERM || sig == SIGINT)
        exit_request=1;
}


Server::Server(int port){
    sigset_t mask;
    printf("starting server on port %d\n",port);
    connected=false;
    exitreq=false;
    
    // register standard connection types, non-standards
    // should have been done by now.
    regStdCons();
    // now we have connection types, we can register the
    // component types
    ComponentType::initAll();
    
    // signals we handle
    memset(&act,0,sizeof(act));
    act.sa_handler = serv_hdl;
    if(sigaction(SIGTERM,&act,0) || 
       sigaction(SIGINT,&act,0) || 
       sigaction(SIGPIPE,&act,0))
        throw Exception("server cannot set signals");
    
    // signals we set to be blocked during the select (we'll still
    // get them, just after the timeout)
    sigemptyset(&mask);
    sigaddset(&mask,SIGTERM);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGPIPE);
    if(sigprocmask(SIG_BLOCK,&mask,&orig_mask)<0)
        throw Exception("cannot set signal mask");
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0)
        throw Exception("cannot create socket");
    
    int yes=1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
        throw Exception("cannot setsockopt");
    
    struct sockaddr_in serv_addr;
    
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
        throw Exception("cannot bind server socket");
    
    // we weirdly get an accept() called if a client terminated its connection
    // with a broken pipe. This will stop that.
    int flags;
    flags = fcntl(listenfd,F_GETFL,0);
    fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
    
    // and we're listening
    listen(listenfd,1);  // backlog of 1
    printf("Server is now listening.\n\n\n");
}



bool Server::process() {
    if(exit_request || exitreq){
        return false;
    }
    
    
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(listenfd,&fds);
    int maxfd=listenfd;
    
    // go round this loop until we're not locked. Quite
    // often we're not anyway. Locking is a mechanism
    // where the client can tell the server just to spin waiting
    // for messages, rather than picking up each new message
    // in each frame. We go into it with a special LOCK message
    // and leave with an UNLOCK message.
    
    bool locked=false;
    do{
        if(connected){
            FD_SET(clientfd,&fds);
            if(clientfd>maxfd)maxfd=clientfd;
        }
        
        // set up the timeout for polling
        timeout.tv_sec=0;
        timeout.tv_nsec=0;
        int rv = pselect(maxfd+1,&fds,NULL,NULL,&timeout,&orig_mask);
        if(rv<0 && errno!=EINTR) // interrupted system calls are OK.
            throw Exception("read error");
        else if(exit_request || exitreq){
            printf("exit request set\n");
            return false;
        }
        else if(rv>0){
            // only process the sets if there are things waiting
            // and the select call was not interrupted (which leaves
            // the sets undefined)
            if(FD_ISSET(listenfd,&fds)){
                clientfd = accept(listenfd,NULL,0);
                printf("new connection, checking\n");
                if(clientfd<0){
                    printf("accept failed!\n");
                } else {
                    if(connected){
                        printf("cannot accept, we're already connected.");
                    }  else {
                        listener->connect();
                        connected=true;
                    }
                }
            }
            if(connected && FD_ISSET(clientfd,&fds)){
                int sizeread = read(clientfd,buffer,BUFFERSIZE);
                printf("Read %d bytes\n",sizeread);
                if(!sizeread){
                    printf("Client disconnected\n");
                    listener->disconnect();
                    connected=false;
                    clientfd=-1;
                    break;
                } else {
                    if(sizeread>=4 && !strncmp(buffer,"LOCK",4)){
                        printf("LOCKING PROTOCOL\n");
                        output("999 LOCKED");
                        locked=true;
                    } else if(sizeread>=4 && !strncmp(buffer,"UNLO",4)){
                        printf("UNLOCKING PROTOCOL\n");
                        output("998 UNLOCKED");
                        locked=false;
                    } else
                        listener->message(buffer,sizeread);
                }
            }
        }
    }while(locked);
    return true;
}


void Server::output(const char *s){
    printf("Sending reply: %s\n",s);
    write(clientfd,s,strlen(s));
}

