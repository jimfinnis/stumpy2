/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "serverbase/model.h"

class ClockComponent : public ComponentType {
    float t;
public:
    ClockComponent() : ComponentType("clock","time"){}
    virtual void init() {
        setOutput(0,tFloat,"time");
        setParams(
                  pMul = new FloatParameter("rate",-100,100,1),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        tFloat->setOutput(ci,0,Time::now() * pMul->get(c) * 0.01);
    }
    
private:
    FloatParameter *pMul;
};

static ClockComponent Clockreg;
