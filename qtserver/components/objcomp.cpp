/**
 * @file components for drawing primitives
 *
 * 
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include "engine/obj.h"

#include <dirent.h>
#include <unistd.h>

static const char **meshNames;

struct mycomparator {
    bool operator()(const char *a,const char *b){
        return strcmp(a,b)<0;
    }
} comparator;
        

class ObjComponent : public ComponentType {
    EnumParameter *primType;
    static ObjMesh **meshes;
    
public:
    static int ct;
    /// called after GL is up.
    static void load(){
        
        // assumes media/meshes contains a directory for each mesh,
        // with the .obj file inside the directory having the name
        // of the directory. For example, "seahorse/seahorse.obj".
        char wd[PATH_MAX];
        getcwd(wd,PATH_MAX);
        chdir("media/meshes");
        DIR *dir = opendir(".");
        
        std::vector<const char *> names;
        while(dirent *ent = readdir(dir)){
            const char *name = ent->d_name;
            if(strlen(name)>=3){
                printf("Adding %s to objlist\n",name);
                name = strdup(name);
                names.push_back(name);
            }
        }
        
        std::sort(names.begin(),names.end(),comparator);
        ct = names.size();
        
        meshNames = new const char * [ct+1];
        meshes = new ObjMesh *[ct];
        for(size_t i=0;i<ct;i++){
            meshNames[i] = names[i];
            char buf[256];
            strcpy(buf,names[i]);
            strcat(buf,".obj");
            printf("Loading %s/%s\n",names[i],buf);
            meshes[i]=new ObjMesh(names[i],buf);
        }
        meshNames[ct]=NULL; // terminator for enum param
        chdir(wd);
    }

    ObjComponent() : ComponentType("obj","render"){}
    virtual void init() {
        setOutput(0,tFlow,"flow");
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

ObjMesh **ObjComponent::meshes;
int ObjComponent::ct=0;
    
void loadObjPrims(){
    ObjComponent::load();
}



static ObjComponent reg;


    
