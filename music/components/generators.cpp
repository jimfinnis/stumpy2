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

#define IN_TICK 0
#define IN_GATE 1
#define IN_REGEN 2
#define IN_REWIND 3

#define OUT_TICK 0
#define OUT_OUTPUT 1
#define OUT_CYCLETICK 2
#define OUT_CYCLECOUNT 3


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
        setInput(IN_TICK,tInt,"tick");
        setInput(IN_GATE,tFloat,"gate");
        setInput(IN_REGEN,tInt,"regenerate");
        setInput(IN_REWIND,tInt,"restart");
        setOutput(OUT_TICK,tInt,"event tick");
        setOutput(OUT_OUTPUT,tFloat,"output");
        setOutput(OUT_CYCLETICK,tInt,"cycle tick");
        setOutput(OUT_CYCLECOUNT,tFloat,"cycle count");
        
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
        
        int tick = tInt->getInput(ci,IN_TICK);
        float gate = (!c->isInputConnected(IN_GATE))?1:
        tFloat->getInput(ci,IN_GATE);
        
        if(tInt->getInput(ci,IN_REWIND))
            d->gen->rewind();
        
        int regen = pAutoRegen->get(c)?1:tInt->getInput(ci,IN_REGEN);
        
        int outtick=0;
        int outcycletick=0;
        
        if(gate>0.5f && tick){
            // recreate if required
            if(!d->gen){
                d->gen = new Morse(
                                   pLen->get(c),
                                   pDepth->get(c),
                                   pSymmetric->get(c),
                                   pPerms->get(c));
            }
            // regen if required
            if(regen)d->gen->reset();
            
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
        tFloat->setOutput(ci,OUT_OUTPUT,d->output);
        tFloat->setOutput(ci,OUT_CYCLECOUNT,d->cyclecount);
        tInt->setOutput(ci,OUT_CYCLETICK,outcycletick);
        tInt->setOutput(ci,OUT_TICK,outtick);
    }
};
static ThueMorse tmreg;
