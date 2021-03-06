/**
 * @file env.cpp
 * @brief  
 * Envelope generator. Each level consists of [time,level].
 * There is an implicit [0,0] at the start.
 *
 */

#include <math.h>
#include "model.h"
#include "../globals.h"
#include "time.h"

static const char *modeNames[]={
    "retrig", // can be restarted during its run
    "noretrig", // must finish before being restarted (if trig is held high, repeats)
    "freerun", // constantly repeats
    "oneshot", // never terminates (but signals done)
    NULL
};

#define MODE_RETRIG 0
#define MODE_NORETRIG 1
#define MODE_FREERUN 2
#define MODE_ONESHOT 3


struct EnvGenData {
    float start; // time elapsed; -1 is not running
    int nextstage; // stage we are waiting for, undef if start<0
    float op; // output
    bool oneshotdone;
};

class EnvGen : public ComponentType {
    EnvelopeParameter *pEnv;
    EnumParameter *pMode;
    IntParameter *pPower2;
public:
    EnvGen() : ComponentType("env","time"){}
    virtual void init(){
        setInput(0,tInt,"trigger");
        setOutput(0,tFloat,"out");
        setOutput(1,tInt,"finish");
        
        setParams(pMode=new EnumParameter("mode",modeNames,0),
                  pPower2 = new IntParameter("rate powerof2",-4,10,0),
                  pEnv=new EnvelopeParameter("env"),
                  NULL);
    }
    virtual void initComponentInstance(ComponentInstance *c){
        EnvGenData *d = new EnvGenData();
        c->privateData = (void *)d;
        d->start = -1;
        d->op = 0;
        d->oneshotdone=false;
    }
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((EnvGenData *)c->privateData);
    }
    
    
    virtual void run(ComponentInstance *ci,int out){
        EnvGenData *d = (EnvGenData *)ci->privateData;
        Component *c = ci->component;
        Envelope& e = pEnv->get(c);
        
        int trig;
        // always trigger if not connected.
        if(!c->isInputConnected(0))trig=1;
        else trig = tInt->getInput(ci,0);
        
        int finishout=0;
        
        // do we retrigger?
        bool retrig=false;
        switch(pMode->get(c)){
        case MODE_RETRIG: // we retrigger if input high
            if(trig)retrig=true;break;
        case MODE_ONESHOT: // we retrigger if input high AND we've never done before
            if(trig && d->start<0 && !d->oneshotdone)retrig=true;break;
        case MODE_NORETRIG: // we retrigger if input high AND we're done
            if(trig && d->start<0)retrig=true;break;
        case MODE_FREERUN: // we retrigger when we're done
            if(d->start<0)retrig=true;break;
        }
        
        
        c->dprintf("Trig=%s retrig=%s start=%f nextstage=%d OSD=%s",
                   trig?"Y":"N",
                   retrig?"Y":"N",
                   d->start,d->nextstage,
                   d->oneshotdone?"Y":"N");
        
        if(retrig){
            d->start = Time::now();
            d->nextstage=0;
            d->op=0;
        }
        
        float mul = powf(2.0,(float)pPower2->get(c));
        
        if(d->start>=0){
            // running
            float t = Time::now() - d->start;
            
            t *= mul;
            
            while(t>=e.times[d->nextstage]){
                // we have hit the next stage
                if(++d->nextstage == ENVSIZE){
                    // we have run out of envelope!
                    d->start = -1;
                    d->oneshotdone=true;
                    finishout=1;
                    break;
                }
            }
            
            if(d->start>=0){ // are we *still* running?
                // calculate the level - there is an implicit level 0 at 
                // time 0.
                float l1 = d->nextstage ? e.levels[d->nextstage-1] : 0;
                float t1 = d->nextstage ? e.times[d->nextstage-1] : 0;
                
                float l2 = e.levels[d->nextstage];
                float t2 = e.times[d->nextstage];
                c->dprintf("time %f: waiting for %d, t1=%f,l1=%f  t1=%f,l2=%f\n",
                       t-t1,d->nextstage,t1,l1,t2,l2);
                
                // interpolate and deal with zero-length steps
                if(t2-t1 > 0.0001f){
                    float a = (t-t1)/(t2-t1);
                    d->op = a*l2 + (1.0f-a)*l1;
                } else {
                    d->op = l2; // use the second entry
                }
            }
        }
        c->dprintf("Out=%f",d->op);
        tFloat->setOutput(ci,0,d->op);
        tInt->setOutput(ci,1,finishout);
    }
    
};
static EnvGen envreg;
