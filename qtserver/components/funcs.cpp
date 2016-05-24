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
}

class FuncComponent : public ComponentType {
public:
    FuncComponent() : ComponentType("func","maths") {
        setInput(0,T_FLOAT,"x");
        setInput(1,T_FLOAT,"y");
        setOutput(0,T_FLOAT,"f(x+y)");
        setParams(
                  pAdd = new FloatParameter("add",-100,100,0),
                  pMul = new FloatParameter("mul",-100,100,1),
                  pFunc = new EnumParameter("func",funcNames,0),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float a = (ci->getInput(0).f+pAdd->get(c))*pMul->get(c);
        float b = (ci->getInput(1).f+pAdd->get(c))*pMul->get(c);
        float v = dofunc(a+b,pFunc->get(c));
        ci->setOutput(0,ConnectionValue::makeFloat(v));
    }
    
private:
    FloatParameter *pAdd,*pMul;
    EnumParameter *pFunc;
};

static FuncComponent reg;
