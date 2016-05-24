#include "engine/engine.h"
#include "model/model.h"

#define NUMMIXERINS 8

class MixerComponent : public ComponentType {
public:
    MixerComponent() : ComponentType("mixer","control"){
        for(int i=0;i<NUMMIXERINS;i++){
            char buf[256];
            sprintf(buf,"clr depth after %d",i);
            mName[i]=strdup(buf);
            pClearDepth[i]=new BoolParameter(mName[i],false);
            addParameter(pClearDepth[i]);
            setInput(i,T_FLOW,"flow");
        }
        setOutput(0,T_FLOW,"flow");
        width=200;
    }
    
    virtual ~MixerComponent(){
        for(int i=0;i<NUMMIXERINS;i++){
            free((void *)mName[i]);
        }
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        for(int i=0;i<NUMMIXERINS;i++){
            ci->getInput(i);
            if(pClearDepth[i]->get(c))
                glClear( GL_DEPTH_BUFFER_BIT );
        }
    }
    
private:
    BoolParameter *pClearDepth[NUMMIXERINS];
    const char *mName[NUMMIXERINS];
};

static MixerComponent mixerReg;
