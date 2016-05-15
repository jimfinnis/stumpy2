/**
 * @file ring.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "model/model.h"

class RingComponent : public ComponentType {
public:
    RingComponent() : ComponentType("ring") {
        setInput(0,T_FLOW);
        setInput(1,T_FLOAT);
        setOutput(0,T_FLOW);
    }
    
    virtual void initComponent(Component *c){
        c->setParams(
                     pCount = new IntParameter(2,100),
                     pRad = new FloatParameter(0,100),
                     pScale = new FloatParameter(0,10),
                     pRadMod = new FloatParameter(-10,10),
                     pScaleMod = new FloatParameter(-10,10),
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
            rot.setRotY(theta);
            m = translate*rot;
            m = scale*m;
        
            ms->mul(&m);
            ci->getInput(0);
            ms->pop();
        }
    }
    
    
private:
    FloatParameter *pScale,*pRadMod,*pScaleMod,*pRad;
    IntParameter *pCount;
};
          
    
static RingComponent ringreg;
