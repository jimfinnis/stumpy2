/**
 * @file math.cpp
 * @brief  Brief description of file.
 *
 */

#include <math.h>
#include "model.h"
#include "../perlin.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class AddComponent : public ComponentType {
public:
    AddComponent() : ComponentType("add","maths"){}
    virtual void init() {
        setInput(0,tFloat,"x");
        setInput(1,tFloat,"y");
        setOutput(0,tFloat,"x+y");
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

        
        tFloat->setOutput(ci,0,a+b);
    }
    
private:
    FloatParameter *pAdd1,*pMul1,*pAdd2,*pMul2;
};

static AddComponent addreg;

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
                  pAddIn1 = new FloatParameter("add-in-x",-100,100,0),
                  pMulIn1 = new FloatParameter("mul-in-x",-100,100,1),
                  pAddIn2 = new FloatParameter("add-in-y",-100,100,0),
                  pMulIn2 = new FloatParameter("mul-in-y",-100,100,1),
                  pFunc = new EnumParameter("func",funcNames,0),
                  pMulOut = new FloatParameter("mul-out",-100,100,1),
                  pAddOut = new FloatParameter("add-out",-100,100,0),
                     NULL
                     );
    }
    
    virtual void run(ComponentInstance *ci,int outnum){
        Component *c = ci->component;
        
        float in1 = (tFloat->getInput(ci,0)+pAddIn1->get(c))*pMulIn1->get(c);
        float in2 = (tFloat->getInput(ci,0)+pAddIn2->get(c))*pMulIn2->get(c);
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


struct PCData {
    PerlinNoise p;
    float prev;
};

class PerlinComponent : public ComponentType {
    FloatParameter *pAddIn,*pMulIn1;
    FloatParameter *pMulIn2;
    FloatParameter *pAddOut,*pMulOut;
    IntParameter *pOctaves;
    FloatParameter *pPersist;
public:
    PerlinComponent() : ComponentType("perlin","maths"){}
    virtual void init(){
        setInput(0,tFloat,"x");
        setInput(1,tFloat,"y");
        setOutput(0,tFloat,"perlin(x+y)");
        setOutput(1,tInt,"zerocrosstrig");
        setParams(
                  pOctaves = new IntParameter("octaves",1,8,2),
                  pPersist = new FloatParameter("persistence",0,1,0.5),
                  pMulIn1 = new FloatParameter("mul-in-x",-100,100,1),
                  pMulIn2 = new FloatParameter("mul-in-y",-100,100,1),
                  pAddIn = new FloatParameter("add-in",-100,100,0),
                  pMulOut = new FloatParameter("mul-out",-100,100,1),
                  pAddOut = new FloatParameter("add-out",-100,100,0),
                  NULL
                  );
    }
    virtual void initComponentInstance(ComponentInstance *c){
        PCData *d = new PCData();
        d->prev = 1;
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((PCData *)c->privateData);
    }
        
    virtual void run(ComponentInstance *ci,int outnum){
        Component *c = ci->component;
        PCData *d = (PCData *)ci->privateData;
        d->p.mOctaves = pOctaves->get(c);
        d->p.mPersistence = pPersist->get(c);
        
        float in1,in2;
        
        // if neither input connected, use the time (as input 1)
        if(!c->isInputConnected(0) && !c->isInputConnected(1)){
            in1 = Time::now()*pMulIn1->get(c);;
            in2 = 0;
        }  else {
            in1 = tFloat->getInput(ci,0)*pMulIn1->get(c);
            in2 = tFloat->getInput(ci,0)*pMulIn2->get(c);
        }
        float out = d->p.get(in1+in2+pAddIn->get(c));
        out *= pMulOut->get(c);
        out += pAddOut->get(c);
        
        int zerocrossed;
        if(sgn<float>(out) != sgn<float>(d->prev))
            zerocrossed=1;
        else
            zerocrossed=0;
        d->prev = out;
        
        tFloat->setOutput(ci,0,out);
        tInt->setOutput(ci,1,zerocrossed);
    }
        
};
static PerlinComponent perlinreg;

