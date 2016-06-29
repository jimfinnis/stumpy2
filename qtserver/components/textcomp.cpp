/**
 * @file texture.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include <unistd.h>

static const char *texFiles[] = 
{
"AladdinBody.tga",
"AladdinHead.tga",
"banner.tga",
"bigrock1.tga",
"bslogo.tga",
"font.tga",
"grass.tga",
"highrock.tga",
"Letys3.tga",
"micrologo.tga",
"moon.tga",
"rock.tga",
"roundmask.tga",
"sand.tga",
"snow.tga",
"star.tga",
"sun.tga",
"terrain.tga",
"test.tga",
    NULL
};

class TextureComponent : public ComponentType {
    EnumParameter *pTex;
    static Texture **textures;
    
public:
    static int ct;
    /// called after GL is up.
    static void load(){
        char wd[PATH_MAX];
        getcwd(wd,PATH_MAX);
        if(chdir("media"))
            throw Exception().set("cannot change to media directory");
        
        for(ct=0;;ct++){
            if(!texFiles[ct])break;
        }
        
        TextureManager *tMgr = TextureManager::getInstance();
        textures = new Texture *[ct];
        for(int i=0;i<ct;i++){
            textures[i] = tMgr->createOrFind(texFiles[i]);
            printf("Done %s\n",texFiles[i]);
        }
        chdir(wd);
    }

    TextureComponent() : ComponentType("texture","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setOutput(0,tFlow,"flow");
        setParams(pTex = new EnumParameter("texture",texFiles,0),
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        int n = pTex->get(c) % ct;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        s->texture = textures[n];
        tFlow->getInput(ci,0);
        sm->pop();
    }
};

void loadTextures(){
    TextureComponent::load();
}


Texture **TextureComponent::textures;
int TextureComponent::ct=0;
    
static TextureComponent reg;
