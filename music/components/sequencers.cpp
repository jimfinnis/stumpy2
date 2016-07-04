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
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        SeqData *d = new SeqData();
        c->privateData = (void *)d;
        d->n = 0;
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
        if(len==0){
            output = 0;
        } else {
            if(step) {
                d->n = (d->n+1)%len;
            }
            output = s[d->n] - '0';
        }
        tFloat->setOutput(ci,0,output);
    }
};

static DenarySequencer denreg;
