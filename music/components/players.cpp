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
        setInput(3,tFloat,"dur mult");
        setOutput(0,tFlow,"flow");
        setParams(
                  pChan=new IntParameter("channel",0,15,0),
                  pGapSecs = new FloatParameter("gapsecs",0,1,0),
                  pVel=new FloatParameter("vel",0,64,50),
                  pVelMod=new FloatParameter("velmod",-64,64,0),
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
        
        // have to always call this.
        BitField b = tChord->getInput(ci,0);
        float velmod = tFloat->getInput(ci,2);
        float durmul = 
              c->isInputConnected(3) ? tFloat->getInput(ci,3) : 1.0f;
    
        float nextTime = d->startTime + gap*(float)d->curNote;
        if(Time::now() > nextTime && d->curNote>=0){
            float dur = durmul*pDur->get(c)*(float)(1<<pDurPow2->get(c));
            dur *= 60.0/gTempo; // convert beats to seconds
            float vel = pVel->get(c) + pVelMod->get(c)*velmod;
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
            if(ct){
                vel *= gVel;
                simpleMidiPlay(pChan->get(c),notes[d->curNote],vel,dur);
                d->curNote++;
                if(d->curNote==ct){
                    d->curNote=-1;
                }
            }
        }
    }        
};
static ChordPlay cpreg;



struct NPData {
    bool playing;
};

class NotePlay : public ComponentType {
    FloatParameter *pVelMod,*pDur,*pVel;
    IntParameter *pChan,*pDurPow2,*pTranspose;
public:
    NotePlay() : ComponentType("noteplay","music"){}
    virtual void init(){
        width = 150;
        
        setInput(0,tInt,"gate");
        setInput(1,tInt,"notetrig");
        setInput(2,tFloat,"note");
        setInput(3,tFloat,"velmod");
        setInput(4,tChord,"chord");
        setInput(5,tFloat,"dur mult");
        
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pChan=new IntParameter("channel",0,15,0),
                  pVel=new FloatParameter("vel",0,64,50),
                  pVelMod=new FloatParameter("velmod",-64,64,0),
                  pDur = new FloatParameter("duration",0.1,1,0.2),
                  pDurPow2 = new IntParameter("duration-pow2",0,4,0),
                  pTranspose = new IntParameter("transpose",-24,24,0),
                  NULL);
              
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        NPData *d = new NPData();
        c->privateData = (void *)d;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((NPData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        NPData *d = (NPData *)ci->privateData;
        
        int gate;
        if(!c->isInputConnected(0))
            gate = 1;
        else
            gate = tInt->getInput(ci,0);            
        int notetrig = tInt->getInput(ci,1);
        int noteidx = (int)(tFloat->getInput(ci,2)+0.5f);
        float velmod = tFloat->getInput(ci,3);
        BitField b = tChord->getInput(ci,4);
        float durmul = c->isInputConnected(5) ? tFloat->getInput(ci,5) : 1.0f;
        
        if(gate && notetrig){
            float dur = durmul*pDur->get(c)*(float)(1<<pDurPow2->get(c));
            dur *= 60.0/gTempo; // convert beats to seconds
            float vel = pVel->get(c) + pVelMod->get(c)*velmod;
            int trans = pTranspose->get(c);
            // as I said above, Ugly.
            int notes[128];
            int ct=0;
            for(int i=0;i<128;i++){
                if(b.get(i)){
//                    printf("Note set: %d\n",i);
                    int n = i + trans;
                    if(n>=0 && n<128)
                        notes[ct++]=n;
                }
            }
            if(ct){
                int oct = noteidx/ct;
                noteidx %= ct;
                vel *= gVel;
                simpleMidiPlay(pChan->get(c),notes[noteidx]+oct*12,
                               vel,dur);
            }
        }
    }
};
static NotePlay npreg;

    
