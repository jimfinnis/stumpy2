/**
 * @file texture.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include <unistd.h>

static const char **texFileNames = NULL;

// turns on flat lighting

class FlatComponent : public ComponentType {
    
public:
    FlatComponent() : ComponentType("flat","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setOutput(0,tFlow,"flow");
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        s->effect = EffectManager::getInstance()->flatTex;
        ci->getInput(0);
        sm->pop();
    }
};


static FlatComponent reg;
