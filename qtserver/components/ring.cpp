/**
 * @file ring.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"

class RingComponent : public ComponentType {
public:
    RingComponent() : ComponentType("ring","transforms") {
        setInput(0,T_FLOW,"flow");
        setInput(1,T_FLOAT,"mod");
        setOutput(0,T_FLOW,"flow");
        setOutput(1,T_FLOAT,"angle");
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
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
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
            ci->setOutput(1,ConnectionValue::makeFloat(theta));
            rot.setRotZ(theta);
            m = translate*rot;
            m = scale*m;
        
            ms->mul(&m);
            ci->getInput(0);
            ci->setOutput(0,ConnectionValue::makeFlow());
            ms->pop();
        }
    }
    
    
private:
    FloatParameter *pScale,*pRadMod,*pScaleMod,*pRad;
    IntParameter *pCount;
};
          
    
static RingComponent ringreg;
