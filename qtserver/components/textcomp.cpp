/**
 * @file texture.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "serverbase/model.h"
#include <unistd.h>

// filenames
static const char **texFileNames = NULL;

class TextureComponent : public ComponentType {
    EnumParameter *pTex;
    static std::vector<Texture *> textures;
    
public:
    static int ct;
    /// called after GL is up.
    static void load(){
        TextureManager *tMgr = TextureManager::getInstance();
        tMgr->loadSet("media/textures",textures);
        
        ct = textures.size();
        texFileNames = new const char * [ct+1];// allow for terminator
        for(int i=0;i<ct;i++){
            texFileNames[i]=textures[i]->name;
            printf("Got %s\n",texFileNames[i]);
        }
        texFileNames[ct]=NULL;
    }

    TextureComponent() : ComponentType("texture","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setOutput(0,tFlow,"flow");
        setParams(pTex = new EnumParameter("texture",texFileNames,0),
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


std::vector<Texture *> TextureComponent::textures;
int TextureComponent::ct=0;
    
static TextureComponent reg;
