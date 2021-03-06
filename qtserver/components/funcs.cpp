/**
 * @file funcs.cpp
 * @brief  Brief description of file.
 *
 */

#include "serverbase/model.h"
#include <math.h>
static const char *funcNames[]=
{
    "sin(x+y)","cos(x+y)","gauss(x+y)",
    "x % y" , "abs(x+y)",
    NULL
};

inline float dofunc(float x,float y,int i){
    switch(i){
    case 0:
        return sinf(x+y);
    case 1:
        return cosf(x+y);
    case 2:
        x=x+y;
        return (1.0f/(2.0f*3.1415927f))*
              powf(2.71828f,-0.5f*x*x);
    case 3:
        return fmodf(x,y);
    case 4:
        return fabsf(x+y);
    }
    return 0;
}

class FuncComponent : public ComponentType {
public:
    FuncComponent() : ComponentType("func","maths"){}
    virtual void init() {
        setInput(0,tFloat,"x");
        setInput(1,tFloat,"y");
        setOutput(0,tFloat,"f(x)");
        setParams(
                  pMulIn1 = new FloatParameter("mul-in-x",-100,100,1),
                  pAddIn1 = new FloatParameter("add-in-x",-100,100,0),
                  pMulIn2 = new FloatParameter("mul-in-y",-100,100,1),
                  pAddIn2 = new FloatParameter("add-in-y",-100,100,0),
                  pFunc = new EnumParameter("func",funcNames,0),
                  pMulOut = new FloatParameter("mul-out",-100,100,1),
                  pAddOut = new FloatParameter("add-out",-100,100,0),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int outnum){
        Component *c = ci->component;
        
        float in1 = tFloat->getInput(ci,0)*pMulIn1->get(c)+pAddIn1->get(c);
        float in2 = tFloat->getInput(ci,1)*pMulIn2->get(c)+pAddIn2->get(c);
        float out = dofunc(in1,in2,pFunc->get(c));
        out *= pMulOut->get(c);
        out += pAddOut->get(c);
        
        tFloat->setOutput(ci,0,out);
    }
    
private:
    FloatParameter *pAddIn1,*pMulIn1;
    FloatParameter *pAddIn2,*pMulIn2;
    FloatParameter *pAddOut,*pMulOut;
    EnumParameter *pFunc;
};

static FuncComponent reg;
