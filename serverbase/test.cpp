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
    
    T1() : ComponentType("t1","test"){
        setInput(0,T_FLOW,"i1");
        setInput(1,T_FLOAT,"i2");
        setOutput(0,T_FLOW,"o1");
        setParams(p1=new IntParameter("foo",0,10,0),
                  p2=new FloatParameter("bar",0,10,0),NULL);
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ci->getInput(0);
        float t = ci->getInput(1).f * ((float)p1->get(c)+p2->get(c));
        printf("T1: %f\n",t);
        ci->setOutput(0,ConnectionValue::makeFlow());
    }
};
        
class T2 : public ComponentType {
public:
    FloatParameter *p1;
    T2() : ComponentType("t2","test"){
        setOutput(0,T_FLOAT,"o1");
        setParams(p1=new FloatParameter("out",0,10,0),NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float t = p1->get(c);
        ci->setOutput(0,ConnectionValue::makeFloat(t));
    }
};

static T1 t1;
static T2 t2;
        

int main(int argc,char *argv[]){
    
    Server server(65111);
    PatchLibrary lib;
    
    server.setListener(new Controller(&lib,&server));
    for(;;){
        if(!server.process())break;
        lib.run();
        gTimerDevice.tick();
        usleep(1000);
    }
}
