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
                    printf("Cycle!\n");
                    done = 1;
                    d->cycles++;
                    d->n=0;
                }
                
                // is the next "note" a space? If so, we 
                // just carry on
                
                if(isalnum(s[d->n])){
                    printf("Next note is VALID\n");
                    // do a duration scan
                    d->dur = 1;
                    const char *pp = s+d->n;
                    for(int n=1;pp[n] && !isalnum(pp[n]);n++){
                        d->dur++;
                    }
                    printf("Duration is %f\n",d->dur);
                    
                    // set the output
                    d->output=s[d->n]-'0';
                    tick=1;
                    printf("Output is %d\n",d->output);
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

// fisher-yates
inline void shuf(char *s,int len){
    for(int i=len-1;i>0;i--){
        int j = rand()%(i+1);
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

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
            d->output = d->str[d->cur] - '0';
            if(isRandom)d->cur++;
            if(d->cur>=d->len){
                // cycle
                if(isRandom)
                    shuf(d->str,d->len); // no select input, randomize
                d->cur=0;
            }
        
        }
        
        tInt->setOutput(ci,0,tick);
        tFloat->setOutput(ci,1,d->output);
        
    }
};
static DenaryPick denrandreg;
