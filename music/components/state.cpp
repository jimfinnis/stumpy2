/**
 * @file state.cpp
 * @brief  Brief description of file.
 *
 */

#include "model.h"
#include "time.h"
#include "../chordcon.h"
#include "../globals.h"

class Vel : public ComponentType {
    FloatParameter *pVel,*pMod;
    static const int NUMINS = 4;
public:
    Vel() : ComponentType("vel","state"){}
    virtual void init(){
        setInput(0,tFloat,"mod");
        for(int i=0;i<NUMINS;i++){
            setInput(1+i,tFlow,"flow");
        }
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pVel = new FloatParameter("vel",0,1,0.8),
                  pMod = new FloatParameter("mod",-5,5,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float p = gVel;
        gVel *= pVel->get(c) + (pMod->get(c)*tFloat->getInput(ci,0));
        if(gVel<0)gVel=0;
        if(gVel>1)gVel=1;
        for(int i=0;i<NUMINS;i++){
            tFlow->getInput(ci,1+i);
        }
        gVel=p;
    }
                  
};
static Vel velreg;

class Transposer : public ComponentType {
    IntParameter *pTrans,*pOct,*pOctEnforced;
    BoolParameter *pOctForce;
    static const int NUMINS = 4;
public:
    Transposer() : ComponentType("trans","state"){}
    virtual void init(){
        setInput(0,tFloat,"mod");
        for(int i=0;i<NUMINS;i++){
            setInput(1+i,tFlow,"flow");
        }
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pTrans = new IntParameter("trans",-12,12,0),
                  pOct = new IntParameter("oct",-4,4,0),
                  pOctForce = new BoolParameter("enforce octave",false),
                  pOctEnforced = new IntParameter("enforced oct",0,10,2),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int t = gTrans;
        int e = gEnforcedOct;
        gTrans += pTrans->get(c) + 12*pOct->get(c);
        if(pOctForce->get(c))
            gEnforcedOct = pOctEnforced->get(c);
        for(int i=0;i<NUMINS;i++){
            tFlow->getInput(ci,1+i);
        }
        
        gTrans = t;
        gEnforcedOct = e;
    }
                  
};
static Transposer transreg;


class OctLimit : public ComponentType {
    IntParameter *pMinOct,*pMaxOct;
    BoolParameter *pMinOctOn,*pMaxOctOn;
    static const int NUMINS = 4;
public:
    OctLimit() : ComponentType("octavelimit","state"){}
    virtual void init(){
        setParams(
                  pMinOctOn=new BoolParameter("minoct on",false),
                  pMinOct=new IntParameter("minoct",-1,6,2),
                  pMaxOctOn=new BoolParameter("maxoct on",false),
                  pMaxOct=new IntParameter("maxoct",-1,6,3),NULL);
        for(int i=0;i<NUMINS;i++){
            setInput(i,tFlow,"flow");
        }
        setOutput(0,tFlow,"flow");
    }
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int oldmin = gMinOct, oldmax = gMaxOct;
        
        if(pMinOctOn->get(c))
            gMinOct = pMinOct->get(c);
        if(pMaxOctOn->get(c))
            gMaxOct = pMaxOct->get(c);
        
        
        for(int i=0;i<NUMINS;i++){
            tFlow->getInput(ci,1+i);
        }
        
        gMinOct = oldmin;
        gMaxOct = oldmax;
    }
};
static OctLimit octlimreg;

class ChordState : public ComponentType {
    static const int NUMINS = 4;
public:
    ChordState() : ComponentType("chordstate","state"){}
    virtual void init(){
        setInput(0,tChord,"chord");
        for(int i=0;i<NUMINS;i++){
            setInput(1+i,tFlow,"flow");
        }
        setOutput(0,tFlow,"flow");
    }
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        BitField oldc = gChord;
        
        if(c->isInputConnected(0))
            gChord = tChord->getInput(ci,0);
        
        for(int i=0;i<NUMINS;i++){
            tFlow->getInput(ci,1+i);
        }
        gChord=oldc;
    }
};

static ChordState chordstatereg;


class DebugMidiState : public ComponentType {
    static const int NUMINS = 4;
public:
    DebugMidiState() : ComponentType("debugmidi","state"){}
    virtual void init(){
        for(int i=0;i<NUMINS;i++){
            setInput(i,tFlow,"flow");
        }
        setOutput(0,tFlow,"flow");
    }
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        bool oldc = gDebugMidi;
        gDebugMidi = true;
        
        for(int i=0;i<NUMINS;i++){
            tFlow->getInput(ci,i);
        }
        gDebugMidi=oldc;
    }
};
    
static DebugMidiState debugmidireg;
