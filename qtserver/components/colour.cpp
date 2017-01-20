/**
 * @file diffusecomp.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include <unistd.h>

class ColourComponent : public ComponentType {
public:
    ColourComponent() : ComponentType("colour","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"r-mod");
        setInput(2,tFloat,"g-mod");
        setInput(3,tFloat,"b-mod");
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pR = new FloatParameter("red",0,1,0),
                  pG = new FloatParameter("green",0,1,0),
                  pB = new FloatParameter("blue",0,1,0),
                  pModR = new FloatParameter("red mod",-1,1,0),
                  pModG = new FloatParameter("green mod",-1,1,0),
                  pModB = new FloatParameter("blue mod",-1,1,0),
                  NULL);
    }

    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        
        // work out the colour
        float modr = tFloat->getInput(ci,1);
        float modg = tFloat->getInput(ci,2);
        float modb = tFloat->getInput(ci,3);
        
        s->overrides |= STO_DIFFUSE;
        s->diffuse.x = pR->get(c) + modr*pModR->get(c);
        s->diffuse.y = pG->get(c) + modg*pModG->get(c);
        s->diffuse.z = pB->get(c) + modb*pModB->get(c);
        // alpha is ignored
        
        ci->getInput(0);
// force always run        tFlow->setOutput(ci,0);
        sm->pop();
    }

private:
    FloatParameter *pR,*pG,*pB;
    FloatParameter *pModR,*pModG,*pModB;
};

static ColourComponent reg;
