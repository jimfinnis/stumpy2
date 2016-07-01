/**
 * @file
 * The controller listens for server commands and uses them to change
 * the model.
 *
 * long description, many sentences.
 * 
 */

#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "server.h"
#include "model.h"

#include <ctype.h>

class Controller;
typedef void (Controller::*CTRMETHOD)(int argc,char *argv[]);

class Controller : public ServerListener {
    
    /// send the currently iterated component type
    void sendCurCT();
    
    virtual void message(const char *s,int size){
        char *q = (char *)s; // so we can block the final char
        char *k = q;
        
        // trim unprintables off the end
        while(*k && *k!=10 && *k!=13)k++;
        *k=0;
        
        
        printf("***** MSG: %s\n",s);
        
        process(q);
    }
    
    virtual void connect(){
        printf("***** CONNECT\n");
    }
    virtual void disconnect(){
        printf("***** DISCONNECT\n");
    }
    
    /*************************************************************************************
     * 
     * Commands
     * 
     ************************************************************************************/
#define DECMETHOD(xx) void method##xx (int argc,char *argv[])
    
    DECMETHOD(Test);
    DECMETHOD(Die);
    DECMETHOD(Clear);
    DECMETHOD(NewPatch);
    DECMETHOD(ConType);
    DECMETHOD(DelPatch);
    DECMETHOD(NewComponent);
    DECMETHOD(DeleteComponent);
    DECMETHOD(LinkComponent);
    DECMETHOD(UnlinkComponentInput);
    DECMETHOD(UnlinkComponentOutput);
    DECMETHOD(SetRunAlways);
    DECMETHOD(ParamSet);
    DECMETHOD(ParamSetStoredString);
    DECMETHOD(RunPatch);
    
    DECMETHOD(StartComps);
    DECMETHOD(NextComp);
    DECMETHOD(CompInName);
    DECMETHOD(CompOutName);
    DECMETHOD(CompParam);
    DECMETHOD(CompEnum);
    
    /// stored strings for commands which need them
    char storedStrings[10][1024];
    
    
    /// output to server if there is one
    
    void output(const char *s,...);
    
    
    /// useful structure storing name -> method mappings
    struct {
        const char *name;
        int argc;
        CTRMETHOD method;
    } commands[32];
    int commandct;
    
    void regCommand(const char *name,int argc,CTRMETHOD method){
        printf("Command registered: %s\n",name);
        commands[commandct].name = name;
        commands[commandct].argc = argc;
        commands[commandct++].method=method;
    }
    
    
    /// split the input into tokens - a command, and up to 16 arguments
    
    void process(char *q){
        char *argv[16];
        int argc=0;
        
        if(*q == ':'){
            q++;
            if(*q>='9' || *q<'0')
                server->fail(SE_BADSTRING);
            // a string parameter for a subsequent command. Stash it.
            // This breaks statelessness, but as the server is all about
            // state (i.e. updating a model) it's not a problem
            int stringNumber = (*q++)-'0';
            strncpy(storedStrings[stringNumber],q,1024);
            server->success();
        } else {
            char *command = strtok(q," \t");
            if(!command)
                printf("empty command\n");
            else {
                while(char *s = strtok(NULL," \t")){
                    if(argc==16)
                        throw new Exception("too many args in command",command);
                    argv[argc++]=s;
                }
                
                // look up the command
                int i;
                for(i=0;i<commandct;i++){
                    if(!strcmp(commands[i].name,command)){
                        if(argc!=commands[i].argc){
                            server->fail(SE_BADARGC);
                        } else {
                            try{
                                (this->*(commands[i].method))(argc,argv);
                            } catch(int n) {
                                // catch numeric exceptions
                                server->fail(n);
                            }
                        }
                        break;
                    }
                }
                if(i==commandct){
                    printf("UNKNOWN COMMAND %s\n",command);
                    server->fail(SE_UNKNOWNCOMMAND);
                }
            }
        }
    }
    
    
    PatchLibrary *library; //!< the library I'm controlling
    Server *server; //!< the server I answer to
    
    
    
public:
    
    
    /// will register commands and set up model pointers, etc.
    Controller(PatchLibrary *l,Server *s);
};


#endif /* __CONTROLLER_H */
