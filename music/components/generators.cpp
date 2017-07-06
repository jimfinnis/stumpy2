/**
 * @file generators.cpp
 * @brief Repeating sequence generators, which take create a sequence
 * randomly from a set of parameters repeatably.
 *
 */

#include "../midi.h"
#include "model.h"
#include "time.h"
#include "../globals.h"
#include "generators.h"

#define INTM_TICK 0
#define INTM_GATE 1
#define INTM_REGEN 2
#define INTM_REWIND 3

#define OUTTM_TICK 0
#define OUTTM_OUTPUT 1
#define OUTTM_CYCLETICK 2
#define OUTTM_CYCLECOUNT 3


struct TMData {
    Morse *gen;
    int cyclecount;
    int output;
    int lastTick; // previous tick value to detect true rising edge
};

class ThueMorse : public ComponentType {
    IntParameter *pLen,*pDepth;
    StringParameter *pPerms;
    BoolParameter *pSymmetric,*pAutoRegen;
    
public:
    ThueMorse() : ComponentType("thuemorse","generators"){}
    virtual void init(){
        setInput(INTM_TICK,tInt,"tick");
        setInput(INTM_GATE,tFloat,"gate");
        setInput(INTM_REGEN,tInt,"regenerate");
        setInput(INTM_REWIND,tInt,"restart");
        setOutput(OUTTM_TICK,tInt,"event tick");
        setOutput(OUTTM_OUTPUT,tFloat,"output");
        setOutput(OUTTM_CYCLETICK,tInt,"cycle tick");
        setOutput(OUTTM_CYCLECOUNT,tFloat,"cycle count");
        
        setParams(
                  pLen = new IntParameter("length",3,100,5),
                  pDepth = new IntParameter("depth",2,10,4),
                  pPerms = new StringParameter("perms","0123456789"),
                  pSymmetric = new BoolParameter("symmetric",false),
                  pAutoRegen = new BoolParameter("auto regen",false),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        TMData *d = new TMData();
        c->privateData = (void *)d;
        d->gen = NULL;
        d->output = 0;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *ci){
        TMData *d = (TMData *)ci->privateData;
        d->cyclecount=0;
        if(d->gen)
            delete d->gen;
        delete d;
    }
    
    /// when a component parameter changes, all instances are informed
    virtual void onParamChanged(ComponentInstance *ci,Parameter *p){
        TMData *d = (TMData *)ci->privateData;
        // just clear the generator so a new one will be made
        d->gen=NULL;
        d->cyclecount=0;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        
        
        Component *c = ci->component;
        TMData *d = (TMData *)ci->privateData;
        
        int tick = tInt->getInput(ci,INTM_TICK);
        float gate = (!c->isInputConnected(INTM_GATE))?1:
        tFloat->getInput(ci,INTM_GATE);
        
        if(tInt->getInput(ci,INTM_REWIND))
            d->gen->rewind();
        
        int regen = pAutoRegen->get(c)?1:tInt->getInput(ci,INTM_REGEN);
        
        int outtick=0;
        int outcycletick=0;
        
        // regen if required
        if(regen)d->gen->reset();
        
        if(gate>0.5f && tick){
            // recreate if required
            if(!d->gen){
                d->gen = new Morse(
                                   pLen->get(c),
                                   pDepth->get(c),
                                   pSymmetric->get(c),
                                   pPerms->get(c));
            }
            
            // get next value from the sequence
            d->output = d->gen->next();
            outtick = 1;
            if(d->gen->cycled()){
                outcycletick=1;
                d->cyclecount++;
            }
            // output only when the output changes
        }
        // these are impulses and so update all the time
        tFloat->setOutput(ci,OUTTM_OUTPUT,d->output);
        tFloat->setOutput(ci,OUTTM_CYCLECOUNT,d->cyclecount);
        tInt->setOutput(ci,OUTTM_CYCLETICK,outcycletick);
        tInt->setOutput(ci,OUTTM_TICK,outtick);
    }
};
static ThueMorse tmreg;

#define INRW_TICK 0
#define INRW_GATE 1
#define OUTRW_TICK 0
#define OUTRW_OUTPUT 1

struct RWData {
    int cur;
    int dir;
};

class RandomWalk : public ComponentType {
    StringParameter *pVals;
    BoolParameter *pWrap;
    FloatParameter *pDirChangeProb;
    
public:
    RandomWalk() : ComponentType("randomwalk","generators"){}
    virtual void init(){
        setInput(INRW_TICK,tInt,"tick");
        setInput(INRW_GATE,tFloat,"gate");
        
        setOutput(OUTRW_TICK,tInt,"event tick");
        setOutput(OUTRW_OUTPUT,tFloat,"output");
        
        setParams(
                  pVals = new StringParameter("vals","012345679"),
                  pWrap = new BoolParameter("wrap",true),
                  pDirChangeProb = new FloatParameter("dirchangeprob",0,1,0.7f),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        RWData *d = new RWData();
        c->privateData = (void *)d;
        d->cur=-1; // will reset to middle
        d->dir=1;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *ci){
        RWData *d = (RWData *)ci->privateData;
        delete d;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        
        if(out == OUTRW_TICK){
            Component *c = ci->component;
            RWData *d = (RWData *)ci->privateData;
            int tick = tInt->getInput(ci,INTM_TICK);
            float gate = (!c->isInputConnected(INTM_GATE))?1:
            tFloat->getInput(ci,INTM_GATE);
            
            int outval=0;
            int tickout=0;
            
            if(gate>0.5f && tick){
                const char *s = pVals->get(c);
                int len = strlen(s);
                if(len){
                    if(d->cur < 0 )
                        d->cur = len/2;
                    
                    if(d->cur<0){
                        if(pWrap->get(c))
                            d->cur = len-1;
                        else {
                            d->cur=0;
                            d->dir *= -1;
                        }
                    } else if(d->cur==len){
                        if(pWrap->get(c))
                            d->cur = 0;
                        else {
                            d->cur=len-1;
                            d->dir *= -1;
                        }
                    } else if(drand48()<pDirChangeProb->get(c)){
                        d->dir *= -1;
                    }
                    
                    outval = hexdigit(s[d->cur]);
                    tickout=1;
                    d->cur += d->dir;
                }
            }
            tInt->setOutput(ci,OUTRW_TICK,tickout);
            tFloat->setOutput(ci,OUTRW_OUTPUT,outval);
        }
    }
};

static RandomWalk regrandw;
