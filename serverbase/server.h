/**
 * @file
 * The server definition.
 *
 * 
 */

#ifndef __SERVER_H
#define __SERVER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socketvar.h>
#include <signal.h>

#include "util/exception.h"
#include "errors.h"

/// a listener for the server

class ServerListener {
public:
    virtual void message(const char *s,int size) = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
};

/// this class is used to send responses back when they are required.
/// If we're running client/server, it's the server and responses
/// are actually sent. If we're reading commands from a file, it's
/// actually a dummy which exits the program with an error if we
/// call fail().

class Responder {
public:
    virtual void success()=0;
    virtual void success(int n)=0;
    virtual void fail(int n)=0;
    virtual void die()=0;
    virtual void output(const char *buf)=0;
};

/// the server handles the communication from the client. There
/// can only be one client connected at a time; anything else would
/// be silly.

class Server : public Responder {
    int listenfd; //!< connection listen socket 
    int clientfd; //!< our single actual client connection
    struct sigaction act; //!< signal data
    sigset_t orig_mask; //!< signal data
    timespec timeout; //!< pselect() timeout
    bool connected; //!< connected to the client?
    bool exitreq; //!< send an exit request
    
    ServerListener *listener; //!< our listener, only one at the mo.
    
#define BUFFERSIZE 1024
    char buffer[BUFFERSIZE]; //!< the buffer for reading
public:
    /// start the server, begin listening for connections
    Server(int port);
    
    /// call this as soon as you've created the server
    void setListener(ServerListener *l){
        listener = l;
    }
    
    virtual void die(){
        exitreq=true;
    }
    
    
    /// tick the server, returns false if we're signalled to exit
    bool process();
    
    /// write a string to the client
    virtual void output(const char *s);
    
    /// write a predefined error string (see errors.h)
    virtual void fail(int n){
        char buf[256];
        sprintf(buf,"%03d %s",n,errorStrings[n]);
        output(buf);
    }
    
    /// output the OK message
    virtual void success(){
        fail(0);
    }
    
    /// send a message containing a primitive name
    void sendPrim(const char *s){
        char buf[256];
        sprintf(buf,"401 %s",s);
        output(buf);
    }
    
    void sendPrimsDone(){
        output("402 prims done");
    }
    
    /// output an OK message with a numeric argument
    virtual void success(int n){
        char buf[256];
        sprintf(buf,"000 OK %d",n);
        output(buf);
    }
    
    /// output an exception thrown message, which will be fatal (i.e. the server
    /// will go down after this)
    void fatalException(Exception &e){
        char buf[256];
        sprintf(buf,"999 %s",e.what());
        output(buf);
    }        
};


#endif /* __SERVER_H */
