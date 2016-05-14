/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "model/model.h"

class ClockComponent : public ComponentType {
    float t;
public:
    ClockComponent() : ComponentType("clock") {
        setOutput(0,T_FLOAT);
    }
    
    virtual void initComponentInstance(ComponentInstance *ci){
        ci->privateData = (void *)malloc(sizeof(float));
        *(float *)ci->privateData = 0;
    }
    virtual void shutdownComponentInstance(ComponentInstance *ci){
       free(ci->privateData);
    }
    
    virtual void initComponent(Component *c){
        c->setParams(
                     pMul = new FloatParameter(-100,100),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float *t = (float *)ci->privateData;
        
        ci->setOutput(0,ConnectionValue::makeFloat(*t*pMul->get(c)));
        *t+=0.01f;
    }
    
private:
    FloatParameter *pMul;
};

static ClockComponent Clockreg;
