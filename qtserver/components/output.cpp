#include "engine/engine.h"
#include "model/model.h"

class OutputComponent : public ComponentType {
public:
    OutputComponent() : ComponentType("output","control"){
        setInput(0,T_FLOW);
        setInput(1,T_FLOW);
        setInput(2,T_FLOW);
        setInput(3,T_FLOW);
        
        // no parameters
        setParams(NULL);
        
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        /* Clear the color and depth buffers. */
        glClearColor(0,0,0.4,0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        StateManager *sm = StateManager::getInstance();
        sm->reset();
        ci->getInput(0);
        ci->getInput(1);
        ci->getInput(2);
        ci->getInput(3);
    }
};

static OutputComponent reg;
