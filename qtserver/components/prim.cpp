/**
 * @file components for drawing primitives
 *
 * 
 */

#include "engine/engine.h"
#include "model/model.h"
#include "engine/mesh.h"

static const char *meshNames[]=
{
    "bevcube.x",
    "ring.x",
    "cube.x",
    "sphere2.x",
    "sphere1.x",
    "aladdin.x",
    "massivesphere.x",
    "blob.x",
    NULL
    
};
    

class PrimComponent : public ComponentType {
    IntParameter *primType;
    static Mesh **meshes;
    
public:
    static int ct;
    /// called after GL is up.
    static void load(){
        // load the meshes
        for(ct=0;;ct++){
            if(!meshNames[ct])break;
        }

        meshes = new Mesh *[ct];
        for(int i=0;i<ct;i++){
            meshes[i] = new Mesh("media",meshNames[i]);
            printf("Done %s\n",meshNames[i]);
        }
    }

    PrimComponent() : ComponentType("primitive") {
        setOutput(0,T_FLOW);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int n = primType->get(c) % ct;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->get();
        meshes[n]->render(&(s->view),sm->getx()->top());
    }
    
    virtual void initComponent(Component *c){
        // deliberately set max large so we don't have to worry about it
        c->setParams(primType = new IntParameter(0,100),
                     NULL);
    }
};

Mesh **PrimComponent::meshes;
int PrimComponent::ct=0;
    
void loadPrims(){
    PrimComponent::load();
}


static int iteratorct=0;

void firstPrim(){
    iteratorct=0; 
}
    
const char *nextPrim(){
    if(iteratorct==PrimComponent::ct)return NULL;
    return meshNames[iteratorct++];
}
    
    

static PrimComponent reg;


    
