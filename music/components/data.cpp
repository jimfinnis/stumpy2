/**
 * @file data.cpp
 * @brief  Data sources of various kinds (including Diamond Apparatus)
 *
 */


#define DIAMOND 1

#include "../midi.h"
#include "model.h"

#include <lo/lo.h>


#if DIAMOND
#define NUMDIAMONDCONNS 10
#include <diamondapparatus/diamondapparatus.h>
class DiamondInComponent : public ComponentType {
    FloatParameter *pAdd[NUMDIAMONDCONNS],*pMul[NUMDIAMONDCONNS];
    StringParameter *pTopic;
public:
    DiamondInComponent() : ComponentType("diamond","data"){
        try {
            diamondapparatus::init();
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond initialisation problem : %s\n",e.what());
            exit(1);
        }
    }
    
    ~DiamondInComponent() {
        diamondapparatus::destroy();
    }
        
    virtual void init() {
        width=170;
        addParameter(pTopic=new StringParameter("topic","data"));
        
        for(int i=0;i<NUMDIAMONDCONNS;i++){
            setOutput(i,tFloat,"out");
            char buf[32];
            sprintf(buf,"mul %d",i);
            addParameter(pMul[i]=new FloatParameter(strdup(buf),-100,100,1));
            sprintf(buf,"add %d",i);
            addParameter(pAdd[i]=new FloatParameter(strdup(buf),-100,100,0));
        }
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        try {
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
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        const char *s = pTopic->get(c);
        float o;
        
        try {
            diamondapparatus::Topic t = diamondapparatus::get(s);
            
            if(out<t.size()){
                o = t[out].f();
                o *= pMul[out]->get(c);
                o += pAdd[out]->get(c);
            } else
                o = 0;
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
            o=0;
        }
        tFloat->setOutput(ci,out,o);
    }
};

static DiamondInComponent diamondingen;
#endif

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




struct CCData {
    int prev;
};


/**
 * Send CC msg over MIDI
 */

class MidiControlComponent : public ComponentType {
    IntParameter *pChan,*pCC;
    FloatParameter *pAdd,*pMul;
public:
    MidiControlComponent() : ComponentType("midi-cc","data"){
    }
    virtual void init() {
        setInput(0,tFloat,"value");
        setOutput(0,tFlow,"flow");
        setParams(
                  pChan=new IntParameter("chan",0,16,0),
                  pCC=new IntParameter("cc",0,128,0),
                  pMul=new FloatParameter("mul",-128,128,128),
                  pAdd=new FloatParameter("add",0,128,0),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        CCData *d = new CCData();
        c->privateData = (void *)d;
        d->prev=-10000;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete((CCData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        CCData *d = (CCData *)ci->privateData;
        
        float inf = c->isInputConnected(0)?tFloat->getInput(ci,0):0;
        inf *= pMul->get(c);
        inf += pAdd->get(c);
        
        int in = (int)inf;
        
        if(in!=d->prev){
            d->prev = in;
            simpleMidiCC(pChan->get(c),pCC->get(c),in);
            c->dprintf("Sending %d on chan %d, ctor %d",
                       in,pChan->get(c),pCC->get(c));
        }
    }
};
static MidiControlComponent midiccreg;


