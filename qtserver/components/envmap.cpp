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
    "e0.tga",
    "e1.tga",
    "e2.tga",
    "e3.tga",
    "e4.tga",
    "e5.tga",
    "e6.tga",
    "e7.tga",
    NULL
};

class EnvMapComponent : public ComponentType {
    EnumParameter *pTex;
    FloatParameter *pR,*pG,*pB,*pA;
    FloatParameter *pModR,*pModG,*pModB,*pModA;
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

    EnvMapComponent() : ComponentType("envmap","state"){}
    virtual void init() {
        setInput(0,tFlow,"flow");
        setInput(1,tFloat,"amount-mod"); //amountmod
        setInput(2,tFloat,"r-mod"); //rmod
        setInput(3,tFloat,"g-mod"); //gmod
        setInput(4,tFloat,"b-mod"); //bmod
        setOutput(0,tFlow,"flow");
        setParams(pTex = new EnumParameter("texture",texFiles,0),
                  pA = new FloatParameter("amount",0,1,0.6),
                  pR = new FloatParameter("red",0,1,1),
                  pG = new FloatParameter("green",0,1,1),
                  pB = new FloatParameter("blue",0,1,1),
                  pModA = new FloatParameter("amount mod",-1,1,0),
                  pModR = new FloatParameter("red mod",-1,1,0),
                  pModG = new FloatParameter("green mod",-1,1,0),
                  pModB = new FloatParameter("blue mod",-1,1,0),
                  
                  NULL);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        
        // work out the colour
        
        float moda = tFloat->getInput(ci,1);
        float modr = tFloat->getInput(ci,2);
        float modg = tFloat->getInput(ci,3);
        float modb = tFloat->getInput(ci,4);
        
        float a = pA->get(c) + moda*pModA->get(c);
        
        int n = pTex->get(c) % ct;
        StateManager *sm = StateManager::getInstance();
        State *s = sm->push();
        s->texture2 = textures[n];
        // the envmap is added on, so we modify the colours
        // rather than the alpha
        s->diffuse2.x = a*(pR->get(c) + modr*pModR->get(c));
        s->diffuse2.y = a*(pG->get(c) + modg*pModG->get(c));
        s->diffuse2.z = a*(pB->get(c) + modb*pModB->get(c));
        s->diffuse2.w = 1;
        s->effect = EffectManager::getInstance()->envMapTex;
        ci->getInput(0);
        sm->pop();
    }
};

Texture **EnvMapComponent::textures;

void loadEnvMaps(){
    EnvMapComponent::load();
}

int EnvMapComponent::ct=0;
static EnvMapComponent reg;
