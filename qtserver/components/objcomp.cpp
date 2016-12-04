/**
 * @file components for drawing primitives
 *
 * 
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include "engine/obj.h"

// dir, mesh - MUST BE IN SYNC WITH BELOW
static const char *meshNames[][2]=
{
    {"media/seahorse","seahorse.obj"},
    {"media/wob","wob.obj"},
    {NULL,NULL}
};

// MUST BE IN SYNC WITH ABOVE
static const char *meshShortNames[]=
{
    "seahorse",
    "wob",
    NULL
};
    
    

class ObjComponent : public ComponentType {
    EnumParameter *primType;
    static ObjMesh **meshes;
    
public:
    static int ct;
    /// called after GL is up.
    static void load(){
        // load the meshes
        for(ct=0;;ct++){
            if(!meshNames[ct][0])break;
        }

        meshes = new ObjMesh *[ct];
        for(int i=0;i<ct;i++){
            meshes[i] = new ObjMesh(meshNames[i][0],meshNames[i][1]);
            printf("Done %s/%s\n",meshNames[i][0],meshNames[i][1]);
        }
    }

    ObjComponent() : ComponentType("obj","render"){}
    virtual void init() {
        setOutput(0,tFlow,"flow");
        setParams(primType = new EnumParameter("mesh",meshShortNames,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int n = primType->get(c) % ct;
        StateManager *sm = StateManager::getInstance();
        meshes[n]->render(sm->getx()->top());
    }
};

ObjMesh **ObjComponent::meshes;
int ObjComponent::ct=0;
    
void loadObjPrims(){
    ObjComponent::load();
}



static ObjComponent reg;


    
