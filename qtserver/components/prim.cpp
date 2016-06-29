/**
 * @file components for drawing primitives
 *
 * 
 */

#include "engine/engine.h"
#include "serverbase/model.h"
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
    EnumParameter *primType;
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

    PrimComponent() : ComponentType("primitive","render") {
        setOutput(0,T_FLOW,"flow");
        setParams(primType = new EnumParameter("mesh",meshNames,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int n = primType->get(c) % ct;
        StateManager *sm = StateManager::getInstance();
        meshes[n]->render(sm->getx()->top());
    }
};

Mesh **PrimComponent::meshes;
int PrimComponent::ct=0;
    
void loadPrims(){
    PrimComponent::load();
}



static PrimComponent reg;


    
