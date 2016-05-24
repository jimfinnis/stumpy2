/**
 * @file diffusecomp.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "model/model.h"
#include <unistd.h>

class DiffuseComponent : public ComponentType {
public:
    DiffuseComponent() : ComponentType("diffuse-col","state") {
        setInput(0,T_FLOW,"flow");
        setInput(1,T_FLOAT,"r-mod");
        setInput(2,T_FLOAT,"g-mod");
        setInput(3,T_FLOAT,"b-mod");
        setOutput(0,T_FLOW,"flow");
        
        setParams(
                  pR = new FloatParameter("red",0,1,0),
                  pG = new FloatParameter("green",0,1,0),
                  pB = new FloatParameter("blue",0,1,0),
                  pModR = new FloatParameter("red mod",-1,1,0),
                  pModG = new FloatParameter("green mod",-1,1,0),
                  pModB = new FloatParameter("bleue mod",-1,1,0),
                  NULL);
    }

    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        
        // work out the colour
        float modr =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        float modg =  ci->isInputConnected(2) ? ci->getInput(2).f : 0;
        float modb =  ci->isInputConnected(3) ? ci->getInput(3).f : 0;
        
        s->overrides |= STO_DIFFUSE;
        s->diffuse.x = pR->get(c) + modr*pModR->get(c);
        s->diffuse.y = pG->get(c) + modg*pModG->get(c);
        s->diffuse.z = pB->get(c) + modb*pModB->get(c);
        // alpha is ignored
        
        ci->getInput(0);
        sm->pop();
    }

private:
    FloatParameter *pR,*pG,*pB;
    FloatParameter *pModR,*pModG,*pModB;
};

static DiffuseComponent reg;
