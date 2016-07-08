/**
 * @file env.cpp
 * @brief  Brief description of file.
 *
 */

#include <math.h>
#include "model.h"
#include "../globals.h"
#include "time.h"


class EnvGen : public ComponentType {
    EnvelopeParameter *pEnv;
public:
    EnvGen() : ComponentType("env","time"){}
    virtual void init(){
        setOutput(0,tFloat,"out");
        
        
        setParams(pEnv=new EnvelopeParameter("env"),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
    }
    
    
};
static EnvGen envreg;
