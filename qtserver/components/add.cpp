/**
 * @file add.cpp
 * @brief  Brief description of file.
 *
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

class AddComponent : public ComponentType {
public:
    AddComponent() : ComponentType("add") {
        setInput(0,T_FLOAT);
        setInput(1,T_FLOAT);
        setOutput(0,T_FLOAT);
    }
    
    virtual void initComponent(Component *c){
        c->setParams(
                     pAdd1 = new FloatParameter(-100,100,0),
                     pMul1 = new FloatParameter(-100,100,1),
                     pAdd2 = new FloatParameter(-100,100,0),
                     pMul2 = new FloatParameter(-100,100,1),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float a = (ci->getInput(0).f+pAdd1->get(c))*pMul1->get(c);
        float b = (ci->getInput(1).f+pAdd2->get(c))*pMul2->get(c);
        
        ci->setOutput(0,ConnectionValue::makeFloat(a+b));
        
    }
    
private:
    FloatParameter *pAdd1,*pMul1,*pAdd2,*pMul2;
};

static AddComponent addreg;



