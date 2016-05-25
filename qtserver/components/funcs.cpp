/**
 * @file funcs.cpp
 * @brief  Brief description of file.
 *
 */

#include "model/model.h"
#include <math.h>
static const char *funcNames[]=
{
    "sin","cos","gauss",
    NULL
};

inline float dofunc(float x,int i){
    switch(i){
    case 0:
        return sinf(x);
    case 1:
        return cosf(x);
    case 2:
        return (1.0f/(2.0f*3.1415927f))*
              powf(2.71828f,-0.5f*x*x);
    }
    return 0;
}

class FuncComponent : public ComponentType {
public:
    FuncComponent() : ComponentType("func","maths") {
        setInput(0,T_FLOAT,"x");
        setInput(1,T_FLOAT,"y");
        setOutput(0,T_FLOAT,"f(x)");
        setParams(
                  pMulIn1 = new FloatParameter("mul-in1",-100,100,1),
                  pAddIn1 = new FloatParameter("add-in1",-100,100,0),
                  pMulIn2 = new FloatParameter("mul-in2",-100,100,1),
                  pAddIn2 = new FloatParameter("add-in2",-100,100,0),
                  pFunc = new EnumParameter("func",funcNames,0),
                  pMulOut = new FloatParameter("mul-out",-100,100,1),
                  pAddOut = new FloatParameter("add-out",-100,100,0),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int outnum){
        Component *c = ci->component;
        
        float in1 = ci->getInput(0).f*pMulIn1->get(c)+pAddIn1->get(c);
        float in2 = ci->getInput(1).f*pMulIn2->get(c)+pAddIn2->get(c);
        float out = dofunc(in1+in2,pFunc->get(c));
        out *= pMulOut->get(c);
        out += pAddOut->get(c);
        
        ci->setOutput(0,ConnectionValue::makeFloat(out));
    }
    
private:
    FloatParameter *pAddIn1,*pMulIn1;
    FloatParameter *pAddIn2,*pMulIn2;
    FloatParameter *pAddOut,*pMulOut;
    EnumParameter *pFunc;
};

static FuncComponent reg;
