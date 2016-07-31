/**
 * @file output.cpp
 * @brief  Brief description of file.
 *
 */

// the root component

#include "model.h"

class Output : public ComponentType {
    static const int NUMINS = 4;
public:
    Output() : ComponentType("output","control"){}
    virtual void init(){
        width=150;
        for(int i=0;i<NUMINS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i,tFlow,strdup(buf));
        }
        isRoot=true;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        for(int i=0;i<NUMINS;i++){
            ci->getInput(i);
        }
    }
};

class Mixer : public ComponentType {
    static const int NUMINS = 6;
public:
    Mixer() : ComponentType("mixer","control"){}
    virtual void init(){
        width=170;
        for(int i=0;i<NUMINS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i,tFlow,strdup(buf));
        }
        setOutput(0,tFlow,"flow");
    }
    
    virtual void run(ComponentInstance *ci,int out){
        for(int i=0;i<NUMINS;i++){
            ci->getInput(i);
        }
    }
};

static Mixer mreg;
static Output oreg;
        
class Switcher : public ComponentType {
    static const int NUMINS = 6;
    BoolParameter *pUnit;
    FloatParameter *pAdd,*pMul;
public:
    Switcher() : ComponentType("switcher","control"){}
    virtual void init(){
        width=170;
        setInput(0,tFloat,"select");
        for(int i=0;i<NUMINS;i++){
            setInput(1+i,tAny,"in");
        }
        setOutput(0,tAny,"out");
        
        setParams(pUnit = new BoolParameter("unit in",true),
                  pMul=new FloatParameter("mul",-10,10,1),
                  pAdd=new FloatParameter("add",-10,10,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float select = tFloat->getInput(ci,0);
        
        int numconnected=0;
        for(numconnected=0;numconnected<NUMINS;numconnected++)
            if(!c->isInputConnected(1+numconnected))break;
        
        select *= pMul->get(c);
        select += pAdd->get(c);
        
        if(pUnit->get(c))
            select *= numconnected;
        
        printf("\nSel=%f\n",select);
        
        int s = (int)select;
        if(s>=numconnected)s=numconnected-1;
        else if(s<0)s=0;
        
        printf("nc=%d Input %d\n",numconnected,s);
        
        ConnectionValue &v = tAny->getInput(ci,s+1);
        tAny->setOutput(ci,0,v);
    }
};
static Switcher swReg;    
    
