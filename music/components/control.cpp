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

static const char *threshTypes[]={"inactive","rising","falling"};
#define THR_INACTIVE 0
#define THR_RISING 1
#define THR_FALLING 2

#define THRESHINS 6
struct ThreshData {
    float prev[THRESHINS];
    bool hasprev[THRESHINS];
};

class Threshold : public ComponentType {
    
    FloatParameter *pAdd,*pMul;
    FloatParameter *pThresh[THRESHINS];
    EnumParameter *pType[THRESHINS];
    
public:
    Threshold() : ComponentType("threshold","control"){}
    virtual void init(){
        width = 170;
        setInput(0,tFloat,"input");
        addParameter(pMul=new FloatParameter("mul",-100,100,1));
        addParameter(pAdd=new FloatParameter("add",-100,100,0));
        for(int i=0;i<THRESHINS;i++){
            char buf[32];
            sprintf(buf,"trig %d",i);
            setOutput(i,tInt,strdup(buf));

            sprintf(buf,"level %d",i);
            addParameter(pThresh[i]=new FloatParameter(strdup(buf),
                                                       -1,1,0));
            sprintf(buf,"type %d",i);
            addParameter(pType[i]=new EnumParameter(strdup(buf),
                                                    threshTypes,
                                                    THR_INACTIVE));
        }
    }
        
              
    virtual void initComponentInstance(ComponentInstance *c){
        ThreshData *d = new ThreshData();
        c->privateData = (void *)d;
        for(int i=0;i<THRESHINS;i++){
            d->hasprev[i]=false;
        }
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((ThreshData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        ThreshData *d = (ThreshData *)ci->privateData;
        Component *c = ci->component;
        
        float in = tFloat->getInput(ci,0);
        in *= pMul->get(c);
        in += pAdd->get(c);
        
        float o=0;
        
        float p = d->prev[out];
        float thresh = pThresh[out]->get(c);
        
        if(d->hasprev[out]){
            switch(pType[out]->get(c)){
            default:
            case THR_INACTIVE:break;
            case THR_RISING:
                if(p<thresh && in>=thresh)o=1;
                break;
            case THR_FALLING:
                if(p>thresh && in<=thresh)o=1;
            }
        } else {
            d->hasprev[out]=true;
        }
        d->prev[out]=in;
        tInt->setOutput(ci,out,o);
    }
};

static Threshold thresreg;
