/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "model/model.h"

class MulComponent : public ComponentType {
public:
    MulComponent() : ComponentType("mul") {
        setInput(0,T_FLOAT);
        setInput(1,T_FLOAT);
        setOutput(0,T_FLOAT);
    }
    
    virtual void initComponent(Component *c){
        c->setParams(
                     pAdd1 = new FloatParameter(-100,100),
                     pMul1 = new FloatParameter(-100,100),
                     pAdd2 = new FloatParameter(-100,100),
                     pMul2 = new FloatParameter(-100,100),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float a = (ci->getInput(0).f+pAdd1->get(c))*pMul1->get(c);
        float b = (ci->getInput(1).f+pAdd2->get(c))*pMul2->get(c);
        
        ci->setOutput(0,ConnectionValue::makeFloat(a*b));
        
    }
    
private:
    FloatParameter *pAdd1,*pMul1,*pAdd2,*pMul2;
};

static MulComponent mulreg;
