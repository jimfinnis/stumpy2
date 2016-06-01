/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "model/model.h"
#include "util/time.h"
#include <math.h>

class OscComponent : public ComponentType {
    float t;
public:
    OscComponent() : ComponentType("osc","time") {
        setInput(0,T_FLOAT,"mod");
        setOutput(0,T_FLOAT,"out");
        setParams(
                  pFreq = new FloatParameter("freq",0,5,1),
                  pMod = new FloatParameter("phase mod",-5,5,0),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float mod =  ci->isInputConnected(0) ? ci->getInput(0).f*
                    pMod->get(c): 0;
        
        float freq = pFreq->get(c);
        float v = Time::now()*freq;
        
        printf("%f\n",Time::now());
        
        // phase mod
        v += mod;
        
        ci->setOutput(0,ConnectionValue::makeFloat(sinf(v)));
    }
    
private:
    FloatParameter *pMod,*pFreq;
};

static OscComponent Oscreg;
