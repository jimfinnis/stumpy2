/**
 * @file test.cpp
 * @brief  Brief description of file.
 *
 */
// test components

#include "model.h"

class T1 : public ComponentType {
public:
    IntParameter *p1;
    StringParameter *p2;
    
    T1() : ComponentType("t1","test"){}
    virtual void init(){
        setInput(0,tFlow,"i1");
        setInput(1,tFloat,"i2");
        setOutput(0,tFlow,"o1");
        setParams(p1=new IntParameter("foo",0,10,0),
                  p2=new StringParameter("bar","---"),NULL);
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        ci->getInput(0);
        float t = tFloat->getInput(ci,1) * (float)p1->get(c);
        printf("T1: %f / %s\n",t,p2->get(c));
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
