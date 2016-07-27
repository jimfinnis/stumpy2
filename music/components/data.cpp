/**
 * @file data.cpp
 * @brief  Data sources of various kinds (including Diamond Apparatus)
 *
 */

#include "model.h"
#include <diamondapparatus/diamondapparatus.h>

class DiamondComponent : public ComponentType {
    FloatParameter *pAdd,*pMul;
    StringParameter *pTopic;
public:
    DiamondComponent() : ComponentType("diamond","data"){}
    virtual void init() {
        setOutput(0,tFloat,"out");
        setParams(pTopic=new StringParameter("topic","data"),
                  pMul=new FloatParameter("mul",-100,100,1),
                  pAdd=new FloatParameter("add",-100,100,0),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        try {
            diamondapparatus::init();
            const char *s = pTopic->get(c->component);
            diamondapparatus::subscribe(s);
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
    
    virtual void onParamChanged(ComponentInstance *ci,UNUSED Parameter *p){
        try {
            if(p == pTopic){
                const char *s = pTopic->get(ci->component);
                diamondapparatus::subscribe(s);
            }
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        diamondapparatus::destroy();
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        const char *s = pTopic->get(c);
        try {
            diamondapparatus::Topic t = diamondapparatus::get(s);
            float o;
            o = t[0].f();
            
            o *= pMul->get(c);
            o += pAdd->get(c);
            tFloat->setOutput(ci,0,o);
        } catch(diamondapparatus::DiamondException e){
            printf("Diamond problem : %s\n",e.what());
        }
    }
};

static DiamondComponent diamondgen;




