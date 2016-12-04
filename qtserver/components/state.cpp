/**
 * @file state.cpp
 * @brief  Brief description of file.
 *
 * Various state stuff: alpha, clear...
 */

#include "engine/engine.h"
#include "serverbase/model.h"

class AlphaComponent : public ComponentType {
public:
    AlphaComponent() : ComponentType("alpha","state") {}
    virtual void init(){
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"mod");
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pAlpha = new FloatParameter("alpha",0,1,0.5),
                  pMod = new FloatParameter("mod",-1,1,0),
                  NULL);
    }
    FloatParameter *pAlpha,*pMod;
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        float mod =  tFloat->getInput(ci,1);
        
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        
        s->overrides |= STO_ALPHA;
        s->alpha = pAlpha->get(c) + mod*pMod->get(c);
        
        tFlow->getInput(ci,0);
        sm->pop();
    }
};

static AlphaComponent regalpha;

class ClearComponent : public ComponentType {
public:
    ClearComponent() : ComponentType("clear","state") {}
    virtual void init(){
        setInput(0,tFlow,"flow");
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pCol = new BoolParameter("col",false),
                  pDepth = new BoolParameter("depth",false),
                  pR = new FloatParameter("red",0,1,0),
                  pG = new FloatParameter("green",0,1,0),
                  pB = new FloatParameter("blue",0,1,0),
                  NULL);
    }
    BoolParameter *pCol,*pDepth;
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        int flags = 0;
        if(pCol->get(c))flags |= GL_COLOR_BUFFER_BIT;
        if(pDepth->get(c))flags |= GL_DEPTH_BUFFER_BIT;
        glClearColor(
                     pR->get(c),
                     pG->get(c),
                     pB->get(c),0);
        glClear(flags);
        tFlow->getInput(ci,0);
    }
private:
    FloatParameter *pR,*pG,*pB;
    
};
static ClearComponent regclear;


class WireframeComponent : public ComponentType {
public:
    WireframeComponent() : ComponentType("wire","state") {}
    virtual void init(){
        setInput(0,tFlow,"flow");
        setOutput(0,tFlow,"flow");
    }
    
    // this won't work.
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        tFlow->getInput(ci,0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
};
static WireframeComponent regwire;
