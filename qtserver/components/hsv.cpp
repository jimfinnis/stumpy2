/**
 * @file hsv.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include <unistd.h>

class HSVComponent : public ComponentType {
public:
    HSVComponent() : ComponentType("hsv","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"h-mod");
        setInput(2,tFloat,"s-mod");
        setInput(3,tFloat,"v-mod");
        setOutput(0,tFlow,"flow");
        
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
        float modh =  tFloat->getInput(ci,1);
        float mods =  tFloat->getInput(ci,2);
        float modv =  tFloat->getInput(ci,3);
        
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
