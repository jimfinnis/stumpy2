/**
 * @file readfile.cpp
 * @brief  Brief description of file.
 *
 */

#include "controller.h"
#include "model.h"

class DummyResponder : public Responder {
public:
    virtual void success(){
    }
    virtual void success(int n){
    }
    virtual void fail(int n){
        printf("Error: %d\n",n);
        exit(1);
    }
    virtual void die(){
        printf("Server commanded to die, which is weird in a file\n");
        exit(1);
    }
    virtual void output(const char *buf){
    }
};

void PatchLibrary::readFile(const char *fn){
    DummyResponder dummy;
    Controller c(this,&dummy);
    
    FILE *a = fopen(fn,"r");
    if(!a){
        printf("Cannot open file %s\n",fn);
        exit(1);
    }
    while(!feof(a)){
        char buf[2048];
        char *s=fgets(buf,2048,a);
        if(s){
            printf("COMMAND: %s\n",s);
            c.message(s,strlen(s));
        }
    }
}
