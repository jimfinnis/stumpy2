/**
 * @file ring.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"

class RingComponent : public ComponentType {
public:
    RingComponent() : ComponentType("ring","transforms"){}
    virtual void init () {
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"mod");
        setOutput(0,tFlow,"flow");
        setOutput(1,tFloat,"angle");
        setParams(
                  pCount = new IntParameter("count",2,100,4),
                  pRad = new FloatParameter("radius",0,100,4),
                  pScale = new FloatParameter("scale",0,10,1),
                  pRadMod = new FloatParameter("radius mod",-10,10,0),
                  pScaleMod = new FloatParameter("scale mod",-10,10,0),
                  NULL
                  );
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        float mod =  tFloat->getInput(ci,1);
        
        MatrixStack *ms = StateManager::getInstance()->getx();
        
        int ct = pCount->get(c);
        float step = (2.0f*PI)/(float)ct;
        float theta=0;
        Matrix translate=Matrix::IDENTITY;
        translate.setTranslation(pRad->get(c)+mod*pRadMod->get(c),0,0);
        Matrix rot=Matrix::IDENTITY,m;
        float sc = pScale->get(c)+mod*pScaleMod->get(c);
        Matrix scale=Matrix::IDENTITY;
        scale.setScale(sc,sc,sc);
        for(int i=0;i<ct;i++,theta+=step){
            ms->push();
            tFloat->setOutput(ci,1,theta);
            rot.setRotZ(theta);
            m = translate*rot;
            m = scale*m;
        
            ms->mul(&m);
            tFlow->getInput(ci,0);
            ms->pop();
        }
        tFlow->setOutput(ci,0);
    }
    
    
private:
    FloatParameter *pScale,*pRadMod,*pScaleMod,*pRad;
    IntParameter *pCount;
};
          
    
static RingComponent ringreg;
