/**
 * @file output.cpp
 * @brief  Brief description of file.
 *
 */

// the root component

#include "model.h"

class Output : public ComponentType {
    static const int NUMINS = 4;
public:
    Output() : ComponentType("output","control"){}
    virtual void init(){
        width=150;
        for(int i=0;i<NUMINS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i,tFlow,strdup(buf));
        }
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        for(int i=0;i<NUMINS;i++){
            ci->getInput(i);
        }
    }
};

static Output reg;
        
