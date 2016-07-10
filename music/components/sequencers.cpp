/**
 * @file sequencers.cpp
 * @brief  Brief description of file.
 *
 */

#include <math.h>
#include "model.h"
#include "../globals.h"
#include "time.h"

struct SeqData {
    int n;
    int cycles;
};

class DenarySequencer : public ComponentType {
    StringParameter *pSeq;
public:
    DenarySequencer() : ComponentType("denseq","music"){}
    virtual void init(){
        setInput(0,tInt,"tick");
        setParams(pSeq=new StringParameter("seq","000"),
                  NULL);
        setOutput(0,tFloat,"out");
        setOutput(1,tInt,"done trigger");
        setOutput(2,tFloat,"cycles done");
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        SeqData *d = new SeqData();
        c->privateData = (void *)d;
        d->n = 0;
        d->cycles=0;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((SeqData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        SeqData *d = (SeqData *)ci->privateData;
        int output;
        int step = tInt->getInput(ci,0);
        const char *s = pSeq->get(c);
        int len = strlen(s);
        int done = 0;
        if(len==0){
            output = 0;
        } else {
            if(step) {
                d->n = (d->n+1)%len;
                if(d->n == 0){
                    done = 1;
                    d->cycles++;
                }
            }
            output = s[d->n] - '0';
        }
        tFloat->setOutput(ci,0,output);
        tInt->setOutput(ci,1,done);
        tFloat->setOutput(ci,2,d->cycles);
    }
};

static DenarySequencer denreg;
