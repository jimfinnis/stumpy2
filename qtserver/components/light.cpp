#include "engine/engine.h"
#include "model/model.h"

// Currently the diffuse light works by just setting the light
// up for the rest of the frame. Later it should probably use 
// the stack properly, perhaps using a transform capture on one
// of its inputs.

class DiffuseLightComponent : public ComponentType {
public:
    DiffuseLightComponent() : ComponentType("diffuse") {
        setInput(0,T_FLOW);
        setInput(1,T_FLOAT);
        
        setOutput(0,T_FLOW);
    }
    virtual void initComponent(Component *c){
        c->setParams(
                     pN = new IntParameter(0,3),
                     pR = new FloatParameter(0,1),
                     pG = new FloatParameter(0,1),
                     pB = new FloatParameter(0,1),
                     pModR = new FloatParameter(-1,1),
                     pModG = new FloatParameter(-1,1),
                     pModB = new FloatParameter(-1,1),
                     pStack = new BoolParameter(),
                     NULL
                     );
    }
                     
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        // the light state is actually modified live WITHOUT
        // pushing state - all objects after this one in the traversal
        // are subject to these lights.
        
        StateManager *sm = StateManager::getInstance();
        State *s = sm->get();
        
        // get the light number
        int n = pN->get(c);
        
        // work out the colour
        float mod =  ci->isInputConnected(1) ? ci->getInput(1).f : 0;
        
        s->light.col[n].x = pR->get(c) + mod*pModR->get(c);
        s->light.col[n].y = pG->get(c) + mod*pModG->get(c);
        s->light.col[n].z = pB->get(c) + mod*pModB->get(c);
        
        // and the position in world space
        Matrix *m = sm->getx()->top();
        // rotate a Z-vector by that to get our light
        s->light.dir[n].transform(Vector::Z,*m);
        
        // and run the somewhat irrelevant input
        ci->getInput(0);
    }
    
private:
    FloatParameter *pR,*pG,*pB;
    FloatParameter *pModR,*pModG,*pModB;
    IntParameter *pN;
    BoolParameter *pStack;
};

static DiffuseLightComponent diffreg;
