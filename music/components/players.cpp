/**
 * @file players.cpp
 * @brief  Brief description of file.
 *
 */

#include "../midi.h"
#include "model.h"
#include "time.h"
#include "../chordcon.h"
#include "../globals.h"

struct CPData {
    int curNote;
    float startTime;
};

class ChordPlay : public ComponentType {
    FloatParameter *pVelMod,*pGapSecs,*pDur,*pVel;
    IntParameter *pChan,*pDurPow2,*pTranspose;
public:
    ChordPlay() : ComponentType("chordplay","music"){}
    virtual void init(){
        setInput(0,tChord,"chord");
        setInput(1,tInt,"tick");
        setInput(2,tFloat,"velmod");
        setOutput(0,tFlow,"flow");
        setParams(pChan=new IntParameter("channel",0,15,0),
                  pVel=new FloatParameter("vel",0,64,50),
                  pVelMod=new FloatParameter("velmod",-64,64,0),
                  pGapSecs = new FloatParameter("gapsecs",0,1,0),
                  pDur = new FloatParameter("duration",0.1,1,0.2),
                  pDurPow2 = new IntParameter("duration-pow2",0,4,0),
                  pTranspose = new IntParameter("transpose",-24,24,0),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        CPData *d = new CPData();
        c->privateData = (void *)d;
        d->curNote=0;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((CPData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        CPData *d = (CPData *)ci->privateData;
        float gap = pGapSecs->get(c);
        if(tInt->getInput(ci,1)){
            // tick! start playing the chord
            d->curNote = 0;
            d->startTime = Time::now();
        }
        
        float nextTime = d->startTime + gap*(float)d->curNote;
        if(Time::now() > nextTime && d->curNote>=0){
            BitField b = tChord->getInput(ci,0);
            float dur = pDur->get(c)*(float)(1<<pDurPow2->get(c));
            float vel = pVel->get(c) + 
                  pVelMod->get(c)*tFloat->getInput(ci,2);
            // get the notes. Ugly.
            int notes[128];
            int ct=0;
            int trans = pTranspose->get(c);
            for(int i=0;i<128;i++){
                if(b.get(i)){
                    int n = i + trans;
                    if(n>=0 && n<128)
                        notes[ct++]=n;
                }
            }
            simpleMidiPlay(pChan->get(c),notes[d->curNote],vel,dur);
            d->curNote++;
            if(d->curNote==ct){
                d->curNote=-1;
            }
        }
    }        
};

static ChordPlay cpreg;
    
