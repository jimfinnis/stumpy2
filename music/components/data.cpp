/**
 * @file data.cpp
 * @brief  Data sources of various kinds (including Diamond Apparatus)
 *
 */

#include "model.h"
#include <diamondapparatus/diamondapparatus.h>
#include <lo/lo.h>

class DiamondComponent : public ComponentType {
    FloatParameter *pAdd,*pMul;
    StringParameter *pTopic;
public:
    DiamondComponent() : ComponentType("diamond","data"){}
    virtual void init() {
        setOutput(0,tFloat,"out");
        setParams(pTopic=new StringParameter("topic","data"),
                  pMul=new FloatParameter("mul",-100,100,1),
                  pAdd=new FloatParameter("add",-100,100,0),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        try {
            diamondapparatus::init();
            const char *s = pTopic->get(c->component);
            diamondapparatus::subscribe(s);
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
    
    virtual void onParamChanged(ComponentInstance *ci,UNUSED Parameter *p){
        try {
            if(p == pTopic){
                const char *s = pTopic->get(ci->component);
                diamondapparatus::subscribe(s);
            }
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        diamondapparatus::destroy();
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        const char *s = pTopic->get(c);
        try {
            diamondapparatus::Topic t = diamondapparatus::get(s);
            float o;
            o = t[0].f();
            
            o *= pMul->get(c);
            o += pAdd->get(c);
            tFloat->setOutput(ci,0,o);
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
};

static DiamondComponent diamondgen;


static lo_address lo;
static void sendOsc(const char *s, float *f,int n){
    lo_message msg = lo_message_new();
    for(int i=0;i<n;i++)
        lo_message_add_float(msg,f[i]);
    int ret = lo_send_message(lo,s,msg);
    lo_message_free(msg);
}

#define NUMOSCINS 6

struct OSCData {
    float prev[NUMOSCINS];
    OSCData(){
        for(int i=0;i<NUMOSCINS;i++)
            prev[i]=-1000;
    }
};

/**
 * Send float msg over OSC, typically to supercollider.
 * Sends on 57120 (SC's default port).
 * Nowt to do with oscillators.
 */

class OSCComponent : public ComponentType {
    StringParameter *pTopic;
public:
    OSCComponent() : ComponentType("OSC-out","data"){
        // SuperCollider's port
        lo = lo_address_new(NULL,"57120");
    }
    virtual void init() {
        width=170;
        for(int i=0;i<NUMOSCINS;i++)
            setInput(i,tFloat,"in");
        setOutput(0,tFlow,"flow");
        setParams(pTopic=new StringParameter("topic","/foo"),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        OSCData *d = new OSCData();
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete((OSCData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        OSCData *d = (OSCData *)ci->privateData;
        
        bool changed=false;
        float data[NUMOSCINS];
        int outct=0;
        for(int i=0;i<NUMOSCINS;i++){
            if(c->isInputConnected(i)){
                float in = tFloat->getInput(ci,i);
                data[outct++]=in;
                if(in!=d->prev[i]){
                    d->prev[i]=in;
                    changed=true;
                }
            }
        }
        if(changed){
            sendOsc(pTopic->get(c),data,outct);
        }
    }
    virtual const char *getExtraText(Component *c,char *buf){
        sprintf(buf,"topic:%s",pTopic->get(c));
        return buf;
    }
};
static OSCComponent OSCreg;


