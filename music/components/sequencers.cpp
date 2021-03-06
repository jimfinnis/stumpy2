/**
 * @file sequencers.cpp
 * @brief  Brief description of file.
 *
 */

#include <math.h>
#include <ctype.h>
#include "model.h"
#include "../globals.h"
#include "time.h"
#include "util.h"

struct SeqData {
    int n;
    int cycles;
    int output;
    float dur;
};

#define OUT_EVENTTICK 0
#define OUT_OUTPUT 1
#define OUT_CYCLETICK 2
#define OUT_CYCLECOUNT 3
#define OUT_EVENTDURATION 4


class DenarySequencer : public ComponentType {
    StringParameter *pSeq;
public:
    DenarySequencer() : ComponentType("denseq","music"){}
    virtual void init(){
        setInput(0,tInt,"tick");
        setParams(pSeq=new StringParameter("seq","000"),
                  NULL);
        setOutput(OUT_EVENTTICK,tInt,"event tick");
        setOutput(OUT_OUTPUT,tFloat,"output value");
        setOutput(OUT_CYCLETICK,tInt,"cycle tick");
        setOutput(OUT_CYCLECOUNT,tFloat,"cycle count");
        setOutput(OUT_EVENTDURATION,tFloat,"event duration");
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        SeqData *d = new SeqData();
        c->privateData = (void *)d;
        d->n = -1;
        d->cycles=0;
        d->dur = 0;
        d->output=0;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((SeqData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        SeqData *d = (SeqData *)ci->privateData;
        int tick=0;
        int step = tInt->getInput(ci,0);
        const char *s = pSeq->get(c);
        int len = strlen(s);
        int done = 0;
        if(len==0){
            d->output = 0;
            d->cycles=0;
            d->dur=1;
        } else {
            if(step) {
                // we're stepping
                d->n++;
                if(d->n == len){
                    c->dprintf("Cycle!\n");
                    done = 1;
                    d->cycles++;
                    d->n=0;
                }
                
                // is the next "note" a space? If so, we 
                // just carry on
                
                if(isalnum(s[d->n])){
                    c->dprintf("Next note is VALID\n");
                    // do a duration scan
                    d->dur = 1;
                    const char *pp = s+d->n;
                    for(int n=1;pp[n] && !isalnum(pp[n]);n++){
                        d->dur++;
                    }
                    c->dprintf("Duration is %f\n",d->dur);
                    
                    // set the output
                    d->output=hexdigit(s[d->n]);
                    tick=1;
                    c->dprintf("Output is %d\n",d->output);
                }
            }
        }
        tInt->setOutput(ci,OUT_EVENTTICK,tick);
        tFloat->setOutput(ci,OUT_OUTPUT,d->output);
        tInt->setOutput(ci,OUT_CYCLETICK,done);
        tFloat->setOutput(ci,OUT_CYCLECOUNT,d->cycles);
        tFloat->setOutput(ci,OUT_EVENTDURATION,d->dur);
    }
};

static DenarySequencer denreg;


struct PickData {
    int len;
    int cur;
    int output;
    char *str;
};

class DenaryPick : public ComponentType {
    StringParameter *pVals;
    BoolParameter *pUnit,*pCycle;
public:
    DenaryPick() : ComponentType("denpick","music"){}
    virtual void init(){
        setInput(0,tInt,"tick");
        setInput(1,tFloat,"select");
        setOutput(0,tInt,"event tick");
        setOutput(1,tFloat,"output value");
        setParams(pVals=new StringParameter("vals","0123"),
                  pUnit=new BoolParameter("unit in",true),
                  pCycle=new BoolParameter("cycle",true),
                  
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        PickData *d = new PickData();
        d->str=NULL;
        d->cur=1000000;
        d->output=0;
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        PickData *d = (PickData *)c->privateData;
        if(d->str)
            free(d->str);
        delete d;
    }
    
    // force string to be rescanned when param changes
    virtual void onParamChanged(ComponentInstance *c, Parameter *p){
        PickData *d = (PickData *)c->privateData;
        if(d->str)free(d->str);
        d->str = NULL;
    }
    
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        PickData *d = (PickData *)ci->privateData;
        bool isRandom = !c->isInputConnected(1);
        
        if(!d->str){
            d->str = strdup(pVals->get(c));
            d->len = strlen(d->str);
        }
        
        int tick = tInt->getInput(ci,0);
        float select = tFloat->getInput(ci,1);
        
        if(pUnit->get(c)){
            select *= d->len+0.9999f;
        }
        if(!isRandom)
            d->cur = (int)select;
        else if(!pCycle->get(c))
            d->cur = rand()%d->len;
        if(d->cur<0)d->cur=0;
        if(d->cur>=d->len)d->cur=d->len-1;
        
        if(tick){
            d->output = hexdigit(d->str[d->cur]);
            if(isRandom)d->cur++;
            if(d->cur>=d->len){
                // cycle
                if(isRandom)
                    shuf<char>(d->str,d->len); // no select input, randomize
                d->cur=0;
            }
        
        }
        
        tInt->setOutput(ci,0,tick);
        tFloat->setOutput(ci,1,d->output);
        
    }
};
static DenaryPick denrandreg;



struct BarSwitcherData {
    int idx;
    int tick;
};

class BarSwitcher : public ComponentType {
    static const int NUMINS=6;
    static const int OTHERINS=1;
    StringParameter *pDurs,*pIns;
public:    
    BarSwitcher() : ComponentType("barswitcher","music"){}
    virtual void init(){
        width=170;
        setInput(0,tInt,"tick");
        for(int i=0;i<NUMINS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i+1,tAny,strdup(buf));
        }
        setOutput(0,tAny,"out");
        setOutput(1,tInt,"bar end");
        
        setParams(pDurs=new StringParameter("durs","4444"),
                  pIns=new StringParameter("ins","0000"),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        BarSwitcherData *d = new BarSwitcherData();
        d->idx=0;
        d->tick=0;
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        BarSwitcherData *d = (BarSwitcherData *)c->privateData;
        delete d;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        BarSwitcherData *d = (BarSwitcherData *)ci->privateData;
        int barEnd=0;
        
        const char *durs = pDurs->get(c);
        const char *ins = pIns->get(c);
        
        int len = strlen(durs);
        if(strlen(ins)<len)len=strlen(ins);
        
        if(len==0)
            tAny->setOutput(ci,0,tAny->getInput(ci,OTHERINS+0));
        else {
            // first test may seem unnecessary, but the parameters
            // may have changed
            c->dprintf("idx=%d tick=%d",d->idx,d->tick);
            if(d->idx>=len){
                d->idx=0;
                d->tick=0;
            }
            int curstagelen = hexdigit(durs[d->idx]);
            if(d->tick>=curstagelen){
                barEnd=1;
                d->tick=0;
                d->idx++;
                if(d->idx>=len){
                    d->idx=0;
                    d->tick=0;
                }
            }
            int in = hexdigit(ins[d->idx]);
            if(tInt->getInput(ci,0))
                d->tick++;
            tAny->setOutput(ci,0,tAny->getInput(ci,OTHERINS+in));
        }
        tInt->setOutput(ci,1,barEnd);
    }
};


class BarPicker : public ComponentType {
    StringParameter *pDurs,*pVals;
public:    
    BarPicker() : ComponentType("barpicker","music"){}
    virtual void init(){
        width=170;
        setInput(0,tInt,"tick");
        setOutput(0,tFloat,"out");
        setOutput(1,tInt,"bar end");
        
        setParams(pDurs=new StringParameter("durs","4444"),
                  pVals=new StringParameter("vals","0123"),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        BarSwitcherData *d = new BarSwitcherData();
        d->idx=0;
        d->tick=0;
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        BarSwitcherData *d = (BarSwitcherData *)c->privateData;
        delete d;
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        BarSwitcherData *d = (BarSwitcherData *)ci->privateData;
        int barEnd=0;
        
        const char *durs = pDurs->get(c);
        const char *ins = pVals->get(c);
        
        int len = strlen(durs);
        if(strlen(ins)<len)len=strlen(ins);
        
        if(len==0)
            tInt->setOutput(ci,0,0);
        else {
            c->dprintf("idx=%d tick=%d",d->idx,d->tick);
            // first test may seem unnecessary, but the parameters
            // may have changed
            if(d->idx>=len){
                d->idx=0;
                d->tick=0;
            }
            int curstagelen = hexdigit(durs[d->idx]);
            if(d->tick>=curstagelen){
                barEnd=1;
                d->tick=0;
                d->idx++;
                if(d->idx>=len){
                    d->idx=0;
                    d->tick=0;
                }
            }
            int in = hexdigit(ins[d->idx]);
            if(tInt->getInput(ci,0))
                d->tick++;
            tFloat->setOutput(ci,0,in);
        }
        tInt->setOutput(ci,1,barEnd);
    }
};

static BarSwitcher barreg;
static BarPicker barpick;
