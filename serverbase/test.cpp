/**
 * @file test.cpp
 * @brief  Brief description of file.
 *
 */

#include <unistd.h>

#include "model.h"
#include "controller.h"
#include "server.h"

// test components

class T1 : public ComponentType {
public:
    IntParameter *p1;
    FloatParameter *p2;
    
    T1() : ComponentType("t1","test"){}
    virtual void init(){
        setInput(0,tFlow,"i1");
        setInput(1,tFloat,"i2");
        setOutput(0,tFlow,"o1");
        setParams(p1=new IntParameter("foo",0,10,0),
                  p2=new FloatParameter("bar",0,10,0),NULL);
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ci->getInput(0);
        float t = tFloat->getInput(ci,1) * ((float)p1->get(c)+p2->get(c));
        printf("T1: %f\n",t);
        tFlow->setOutput(ci,0);
    }
};

class T2 : public ComponentType {
public:
    FloatParameter *p1;
    T2() : ComponentType("t2","test"){}
    virtual void init(){
        setOutput(0,tFloat,"o1");
        setParams(p1=new FloatParameter("out",0,10,0),NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float t = p1->get(c);
        tFloat->setOutput(ci,0,t);
    }
};

static T1 t1;
static T2 t2;

int main(int argc,char *argv[]){
    
    try {
        Server server(65111);
        PatchLibrary lib;
        
        server.setListener(new Controller(&lib,&server));
        for(;;){
            if(!server.process())break;
            lib.run();
            gTimerDevice.tick();
            usleep(1000);
        }
    } catch(int x) {
        printf("Error: %s\n",errorStrings[x]);
        exit(1);
    }
}
