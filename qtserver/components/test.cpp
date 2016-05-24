#include "engine/engine.h"
#include "model/model.h"

class TestComponent : public ComponentType {
private:
    IntParameter *param1;
    FloatParameter *param2;
public:
    TestComponent() : ComponentType("test","control"){
        setInput(0,T_FLOW,"??");
        setInput(1,T_FLOW,"??");
        setInput(2,T_FLOAT,"??");
        
        setOutput(0,T_FLOW,"??");
        setOutput(1,T_FLOW,"??");
        setOutput(2,T_FLOAT,"??");
        setParams(param1=new IntParameter("foo",0,10,0),
                  param2=new FloatParameter("bar",0,10,0),NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        if(out==0){
            Component *c = ci->component;
            float p1 = param1->get(c);
            float p2 = param2->get(c);
            
            StateManager *sm = StateManager::getInstance();
            Matrix *m = sm->getx()->push();
            m->identity();
            m->setTranslation(p1,0,0);
            ci->getInput(0);
            m->setTranslation(p2,0,0);
            ci->getInput(1);
            sm->getx()->pop();
            
            float t = ci->getInput(2).f;
            printf("%f\n",t);
        }
    }
};
static TestComponent reg;
