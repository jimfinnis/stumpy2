/**
 * @file
 * Simple transform components.
 *
 * 
 */

#include "engine/engine.h"
#include "model/model.h"

/// base class for all transforms which sets up common parameters

class SimpleTransformComponentType : public ComponentType {
public:
    SimpleTransformComponentType(const char *name) :
    ComponentType(name,"transforms") {
        setInput(0,T_FLOW);
        setInput(1,T_FLOAT);
        setOutput(0,T_FLOW);
        setP();
    }
    
protected:
    
    virtual void setP(){
        setParams(
                     pX = new FloatParameter("x",-100,100,0),
                     pY = new FloatParameter("y",-100,100,0),
                     pZ = new FloatParameter("z",-100,100,0),
                     pModX = new FloatParameter("mod x",-10,10,0),
                     pModY = new FloatParameter("mod y",-10,10,0),
                     pModZ = new FloatParameter("mod z",-10,10,0),
                     NULL);
    }
    FloatParameter *pX,*pY,*pZ,*pModX,*pModY,*pModZ;
};

class MoveComponent : public SimpleTransformComponentType {
public:
    MoveComponent() : SimpleTransformComponentType("move") {}
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
        MatrixStack *ms = StateManager::getInstance()->getx();
        ms->push();
        
        Matrix m=Matrix::IDENTITY;
        m.setTranslation(
                         pX->get(c) + mod*pModX->get(c),
                         pY->get(c) + mod*pModY->get(c),
                         pZ->get(c) + mod*pModZ->get(c));
        ms->mul(&m);
        
        ci->getInput(0);
        
        ms->pop();
    }
};

class ScaleComponent : public SimpleTransformComponentType {
public:
    ScaleComponent() : SimpleTransformComponentType("scale") {}
    
    virtual void setP(){
        setParams(
                  pX = new FloatParameter("x",-100,100,1),
                  pY = new FloatParameter("y",-100,100,1),
                  pZ = new FloatParameter("z",-100,100,1),
                  pModX = new FloatParameter("mod x",-10,10,0),
                  pModY = new FloatParameter("mod y",-10,10,0),
                  pModZ = new FloatParameter("mod z",-10,10,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
        MatrixStack *ms = StateManager::getInstance()->getx();
        ms->push();
        
        Matrix m=Matrix::IDENTITY;
        m.setScale(
                         pX->get(c) + mod*pModX->get(c),
                         pY->get(c) + mod*pModY->get(c),
                         pZ->get(c) + mod*pModZ->get(c));
        ms->mul(&m);
        
        ci->getInput(0);
        
        ms->pop();
    }
};


class RotateComponent : public SimpleTransformComponentType {
public:
    RotateComponent() : SimpleTransformComponentType("rotate") {}
    
    virtual void run(ComponentInstance *ci,UNUSED int out){
        Component *c = ci->component;
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
        float rotx  = pX->get(c) + mod*pModX->get(c);
        float roty  = pY->get(c) + mod*pModY->get(c);
        float rotz  = pZ->get(c) + mod*pModZ->get(c);
        
        MatrixStack *ms = StateManager::getInstance()->getx();
        ms->push();
        
        Matrix m;
        m.setTranslation(0,0,0);
        m.makeRotate(rotx,roty,rotz,Matrix::ROT_YXZ);
        ms->mul(&m);
        ci->getInput(0);
        
        ms->pop();
    }
};


static RotateComponent rreg;
static ScaleComponent sreg;
static MoveComponent mreg;
