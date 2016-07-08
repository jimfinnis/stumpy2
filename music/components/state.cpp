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
public:
    Vel() : ComponentType("vel","state"){}
    virtual void init(){
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"mod");
        setOutput(0,tFlow,"flow");
        
        setParams(
                  pVel = new FloatParameter("vel",0,1,0.8),
                  pMod = new FloatParameter("mod",-5,5,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        float p = gVel;
        gVel *= pVel->get(c) + (pMod->get(c)*tFloat->getInput(ci,1));
        if(gVel<0)gVel=0;
        if(gVel>1)gVel=1;
        tFlow->getInput(ci,0);
        gVel=p;
    }
                  
};
static Vel velreg;
