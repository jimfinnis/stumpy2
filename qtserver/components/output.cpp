#include "engine/engine.h"
#include "serverbase/model.h"

class OutputComponent : public ComponentType {
public:
    OutputComponent() : ComponentType("output","control"){}
    virtual void init(){
        setInput(0,tFlow,"flow");
        setInput(1,tFlow,"flow");
        setInput(2,tFlow,"flow");
        setInput(3,tFlow,"flow");
        
        // no parameters
        setParams(NULL);
        
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        /* Clear the color and depth buffers. */
        glClearColor(0,0,0,0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        StateManager *sm = StateManager::getInstance();
        sm->reset();
        tFlow->getInput(ci,0);
        tFlow->getInput(ci,1);
        tFlow->getInput(ci,2);
        tFlow->getInput(ci,3);
    }
};

static OutputComponent reg;
