/**
 * @file hsv.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "model/model.h"
#include <unistd.h>

class HSVComponent : public ComponentType {
public:
    HSVComponent() : ComponentType("hsv","state") {
        setInput(0,T_FLOW,"flow");
        setInput(1,T_FLOAT,"h-mod");
        setInput(2,T_FLOAT,"s-mod");
        setInput(3,T_FLOAT,"v-mod");
        setOutput(0,T_FLOW,"flow");
        
        setParams(
                  pH = new FloatParameter("hue",0,1,0),
                  pS = new FloatParameter("sat",0,1,0),
                  pV = new FloatParameter("val",0,1,0),
                  pModH = new FloatParameter("hue mod",-1,1,0),
                  pModS = new FloatParameter("sat mod",-1,1,0),
                  pModV = new FloatParameter("val mod",-1,1,0),
                  NULL);
    }

    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        
        // work out the colour
        float modh =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        float mods =  ci->isInputConnected(2) ? ci->getInput(2).f : 0;
        float modv =  ci->isInputConnected(3) ? ci->getInput(3).f : 0;
        
        float hue = pH->get(c) + modh*pModH->get(c);
        float sat = pS->get(c) + mods*pModS->get(c);
        float val = pV->get(c) + modv*pModV->get(c);
        
        s->overrides |= STO_DIFFUSE;
        
        Colour::HSVtoRGB(&s->diffuse.x,&s->diffuse.y,&s->diffuse.z,
                         hue,sat,val);
        // alpha is ignored
        
        ci->getInput(0);
        sm->pop();
    }

private:
    FloatParameter *pH,*pS,*pV;
    FloatParameter *pModH,*pModS,*pModV;
};

static HSVComponent reg;
