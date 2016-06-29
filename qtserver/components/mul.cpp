/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "serverbase/model.h"

class MulComponent : public ComponentType {
public:
    MulComponent() : ComponentType("mul","maths"){}
    virtual void init() {
        setInput(0,tFloat,"x");
        setInput(1,tFloat,"y");
        setOutput(0,tFloat,"x*y");
        setParams(
                     pAdd1 = new FloatParameter("add 1",-100,100,0),
                     pMul1 = new FloatParameter("mul 1",-100,100,1),
                     pAdd2 = new FloatParameter("add 2",-100,100,0),
                     pMul2 = new FloatParameter("mul 2",-100,100,1),
                     NULL
                     );
    }
    
   virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float a = (tFloat->getInput(ci,0)+pAdd1->get(c))*pMul1->get(c);
        float b = (tFloat->getInput(ci,1)+pAdd2->get(c))*pMul2->get(c);
        tFloat->setOutput(ci,0,a*b);
    }
    
private:
    FloatParameter *pAdd1,*pMul1,*pAdd2,*pMul2;
};

static MulComponent mulreg;
