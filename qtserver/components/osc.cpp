/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "serverbase/model.h"
#include "serverbase/util/time.h"
#include <math.h>

class OscComponent : public ComponentType {
    float t;
public:
    OscComponent() : ComponentType("osc","time"){}
    virtual void init() {
        setInput(0,tFloat,"mod");
        setOutput(0,tFloat,"out");
        setParams(
                  pFreq = new FloatParameter("freq",0,5,1),
                  pMod = new FloatParameter("phase mod",-5,5,0),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float mod =  tFloat->getInput(ci,0) * pMod->get(c);
        float freq = pFreq->get(c);
        float v = Time::now()*freq;
        
        // phase mod
        v += mod;
        
        tFloat->setOutput(ci,0,sinf(v));
    }
    
private:
    FloatParameter *pMod,*pFreq;
};

static OscComponent Oscreg;
