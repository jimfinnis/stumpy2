/**
 * @file state.cpp
 * @brief  Brief description of file.
 *
 * Various state stuff: alpha, clear...
 */

#include "engine/engine.h"
#include "model/model.h"

class AlphaComponent : public ComponentType {
public:
    AlphaComponent() : ComponentType("alpha","state") {
        setInput(0,T_FLOW,"flow");
        setInput(1,T_FLOAT,"mod");
        setOutput(0,T_FLOW,"flow");
        
        setParams(
                  pAlpha = new FloatParameter("alpha",0,1,0.5),
                  pMod = new FloatParameter("mod",-1,1,0),
                  NULL);
    }
    FloatParameter *pAlpha,*pMod;
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        
        float modr =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        s->overrides |= STO_ALPHA;
        s->alpha = pAlpha->get(c) + mod*pMod->get(c);
        
        ci->getInput(0);
        sm->pop();
    }
};

static AlphaComponent regalpha;

class ClearComponent : public ComponentType {
public:
    ClearComponent() : ComponentType("clear","state") {
        setInput(0,T_FLOW,"flow");
        setOutput(0,T_FLOW,"flow");
        
        setParams(
                  pCol = new BoolParameter("col",false),
                  pDepth = new BoolParameter("depth",false),
                  NULL);
    }
    BoolParameter *pCol,*pDepth;
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        int flags = 0;
        if(pCol->get(c))flags |= GL_COLOR_BUFFER_BIT;
        if(pDepth->get(c))flags |= GL_DEPTH_BUFFER_BIT;
        glClear(flags);
        ci->getInput(0);
    }
};
static ClearComponent regclear;
