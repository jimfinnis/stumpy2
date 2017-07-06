/**
 * @file time.cpp
 * @brief  Brief description of file.
 *
 */
#include <math.h>
#include "model.h"
#include "../globals.h"
#include "time.h"

// global tempo generator. Sets tempo for all components
// called by it.
class Tempo : public ComponentType {
    static const int NUMINS = 8;
    FloatParameter *pTempo,*pMod;
    
public:
    Tempo() : ComponentType("tempo","time"){}
    virtual void init(){
        width=150;
        setInput(0,tFloat,"mod");
        for(int i=0;i<NUMINS;i++){
            char buf[32];
            sprintf(buf,"in %d",i);
            setInput(i+1,tFlow,strdup(buf));
        }
        setOutput(0,tFlow,"flow");
        setParams(pTempo = new FloatParameter("tempo",20,200,100),
                  pMod = new FloatParameter("mod",-100,100,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float baseTempo = pTempo->get(c);
        float mod = pMod->get(c) * tFloat->getInput(ci,0);
        gTempo = baseTempo+mod;
        
        float prev = gTempo;
        for(int i=0;i<NUMINS;i++){
            ci->getInput(i+1);
        }
        gTempo=prev;
    }
    
    
};
static Tempo regtempo;




struct ClockData {
    float start;
    float prevq[10];
};

// produces regular ticks
class Clock : public ComponentType {
    IntParameter *pPower2;
    FloatParameter *pMul,*pAdd,*pGapBeats;
    static const int NUMOUTS=4;
public:
    Clock() : ComponentType("clock","time"){}
    virtual void init(){
        setParams(pPower2 = new IntParameter("poweroftwo",-4,4,0),
                  pMul = new FloatParameter("mul",0.1,3,1),
                  pAdd = new FloatParameter("add",-100,100,0),
                  pGapBeats = new FloatParameter("gapbeats",0,1,0),
                  NULL);
        
        for(int i=0;i<NUMOUTS;i++)
            setOutput(i,tInt,"tick");
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        ClockData *d = new ClockData();
        c->privateData = (void *)d;
        d->start = Time::now();
        for(int i=0;i<NUMOUTS;i++)
            d->prevq[i]=-1;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((ClockData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        ClockData *d = (ClockData *)ci->privateData;
        Component *c = ci->component;
        
        // get time interval
        float tempo = gTempo * powf(2.0,(float)pPower2->get(c))
              * pMul->get(c) + pAdd->get(c);
        float interval = 60.0/tempo; // convert to BPS
        
        float gap = (60.0*pGapBeats->get(c))/tempo;
        float tout = Time::now()-gap*(float)out;
        
        // then fmod that time with the interval
        float q = fmod(tout,interval);
        // when this crosses zero is when we should tick.
        int tick = (q<d->prevq[out])?1:0;
        d->prevq[out]=q;
        
        tInt->setOutput(ci,out,tick);
    }
    virtual const char *getExtraText(Component *c,char *buf){
        // can't take account of tempo here, sadly; we'd have
        // to get this called every time the tempo changed upstream.
        float t= powf(2.0,(float)pPower2->get(c))
              * pMul->get(c) + pAdd->get(c);
        
        sprintf(buf,"%.3f",t);
        return buf;
    }
};
static Clock regclock;



// produces regular ticks, type 2 (timed in seconds)
class AbsClock : public ComponentType {
    IntParameter *pPower2;
    FloatParameter *pMul,*pAdd,*pGapSecs;
    static const int NUMOUTS=4;
public:
    AbsClock() : ComponentType("absclock","time"){}
    virtual void init(){
        setParams(pPower2 = new IntParameter("poweroftwo",-4,4,0),
                  pMul = new FloatParameter("mul",0.1,3,1),
                  pAdd = new FloatParameter("add",-100,100,0),
                  pGapSecs = new FloatParameter("gapsecs",0,1,0),
                  NULL);
        
        for(int i=0;i<NUMOUTS;i++)
            setOutput(i,tInt,"tick");
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        ClockData *d = new ClockData();
        c->privateData = (void *)d;
        d->start = Time::now();
        for(int i=0;i<NUMOUTS;i++)
            d->prevq[i]=-1;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((ClockData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        ClockData *d = (ClockData *)ci->privateData;
        Component *c = ci->component;
        
        // get time interval, this time absolute
        float interval= powf(2.0,(float)pPower2->get(c)) * pMul->get(c) + pAdd->get(c);
        
        float gap = pGapSecs->get(c);
        float tout = Time::now()-gap*(float)out;
        
        // then fmod that time with the interval
        float q = fmod(tout,interval);
        // when this crosses zero is when we should tick.
        int tick = (q<d->prevq[out])?1:0;
        d->prevq[out]=q;
        
        tInt->setOutput(ci,out,tick);
    }
    virtual const char *getExtraText(Component *c,char *buf){
        float t= powf(2.0,(float)pPower2->get(c))
              * pMul->get(c) + pAdd->get(c);
        
        sprintf(buf,"%.3f",t);
        return buf;
    }
};
static AbsClock regabsclock;





class TickCombiner : public ComponentType {
    static const int NUMINS = 4;
public:
    TickCombiner() : ComponentType("tickcombine","time"){}
    virtual void init(){
        for(int i=0;i<NUMINS;i++)
            setInput(i,tInt,"tick");
        setOutput(0,tInt,"tick");
    }
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        int tick = 0;
        for(int i=0;i<NUMINS;i++){
            if(tInt->getInput(ci,i)){
                tick = 1;
                break;
            }
        }
        tInt->setOutput(ci,0,tick);
    }
};
static TickCombiner tickcombinereg;



struct ClockDivData {
    int ct;
};

class ClockDivider : public ComponentType {
    IntParameter *pDiv;
public:
    ClockDivider() : ComponentType("clockdiv","time"){}
    virtual void init(){
        setInput(0,tInt,"tick");
        setOutput(0,tInt,"tick");
        setParams(pDiv=new IntParameter("div",1,32,2),
                  NULL);
    }
    virtual void initComponentInstance(ComponentInstance *c){
        ClockDivData *d = new ClockDivData();
        c->privateData = (void *)d;
        d->ct=0;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((ClockDivData *)c->privateData);
    }
    virtual void run(ComponentInstance *ci,int out){
        ClockDivData *d = (ClockDivData *)ci->privateData;
        Component *c = ci->component;
        
        int o = 0;
        
        if(tInt->getInput(ci,0)){
            if(++d->ct == pDiv->get(c)){
                o=1;
                d->ct=0;
            }
        }   
        
        tInt->setOutput(ci,0,o);
    }
};
static ClockDivider clockdivreg;



class TickPrint : public ComponentType {
    StringParameter *pStr;
public:
    TickPrint() : ComponentType("tickprint","debug"){}
    virtual void init(){
        setInput(0,tInt,"tick");
        setInput(1,tFloat,"float");
        setOutput(0,tFlow,"flow");
        setParams(pStr = new StringParameter("text","TICK"),NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        int tick = tInt->getInput(ci,0);
        if(tick){
            printf("TickPrint: %s ",pStr->get(c));
            if(c->isInputConnected(1))
                printf("%f ",tFloat->getInput(ci,1));
            printf("\n");
        }
    }
};
static TickPrint regtickprint;


static const char *waveNames[]=
{"sin","saw(ascending)","saw(descending)","triangle","square",NULL};
static const char *waveAbbrev[]={"SN","SA","SD","TR","SQ"};
    
class OscComponent : public ComponentType {
public:
    OscComponent() : ComponentType("osc","time"){}
    virtual void init() {
        setInput(0,tFloat,"mod");
        setOutput(0,tFloat,"out");
        setParams(
                  pWave = new EnumParameter("wave",waveNames,0),
                  pFreq = new FloatParameter("freq (beats)",0,5,1),
                  pPhase = new FloatParameter("phase",-5,5,0),
                  pMod = new FloatParameter("phase mod",-5,5,0),
                  pAmp = new FloatParameter("amp",0,10,1),
                  pOffset = new FloatParameter("offset",-5,5,0),
                  pMinZero = new BoolParameter("min = zero",false),
                  pWidth = new FloatParameter("width (square)",0,1,0.5),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float mod =  tFloat->getInput(ci,0) * pMod->get(c);
        float freq = pFreq->get(c)*(gTempo/60.0f);
        float v = Time::now()*freq;
        
        // phase mod
        v += mod + pPhase->get(c);
        switch(pWave->get(c)){
        default:
        case 0: //sin
            v = sinf(v);break;
        case 1: //ascending saw
            v = (v-floorf(v))*2.0f-1.0f;break;
        case 2: //descending saw
            v = -((v-floorf(v))*2.0f-1.0f);break;
        case 3: //triangle
            v = 2.0f*fabsf(2.0*(v-floorf(v+0.5)))-1.0; //fr. wikipedia "triangle wave"
            break;
        case 4: //square
            // form triangle
            v = fabsf(2.0*(v-floorf(v+0.5)));
            // threshold it with the width
            v = (v<pWidth->get(c))?1:-1;
            break;
        }
        
        float amp = pAmp->get(c);
        float off = pOffset->get(c);
        if(pMinZero->get(c)){
            v += 1.0;
            v *= 0.5f;
        }
        v *= amp;
        v += off;
        
        tFloat->setOutput(ci,0,v);
    }
    virtual const char *getExtraText(Component *c,char *buf){
        sprintf(buf,"%s:%.3f",waveAbbrev[pWave->get(c)],pFreq->get(c));
        return buf;
    }
    
private:
    FloatParameter *pMod,*pFreq,*pPhase,*pAmp,*pOffset,*pWidth;
    EnumParameter *pWave;
    BoolParameter *pMinZero;
};

static OscComponent Oscreg;

class TimeComponent : public ComponentType {
    float t;
public:
    TimeComponent() : ComponentType("time","time"){}
    virtual void init() {
        setOutput(0,tFloat,"time");
        setParams(
                  pMul = new FloatParameter("rate",-100,100,1),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        tFloat->setOutput(ci,0,Time::now() * pMul->get(c) * 0.01);
    }
    
private:
    FloatParameter *pMul;
};

static TimeComponent timereg;


