/**
 * @file linear.cpp
 * @brief  Brief description of file.
 *
 */

#include "engine/engine.h"
#include "model/model.h"

struct lincop {
    lincop(){
        offset=pos=0;
    }
    float offset;
    float pos;
};

class LinearComponent : public ComponentType {
public:
    LinearComponent() : ComponentType("linear","transforms"){
        setInput(0,T_FLOW,"flow");
        setInput(1,T_FLOAT,"mod1");
        setInput(2,T_FLOAT,"mod2");
        setOutput(0,T_FLOW,"flow");
        setOutput(1,T_FLOAT,"pos");
        setOutput(2,T_FLOAT,"crawlscale");
        
        setParams(
                  pCopies = new IntParameter("copies",2,100,4),
                  pSpacing = new FloatParameter("spacing",0,10,2),
                  pSpiral = new FloatParameter("spiral",-1,1,0),
                  pRotate = new FloatParameter("rotate",-4,4,0),
                  pScale = new FloatParameter("scale",0,2,1),
                  
                  pMod1Spacing = new FloatParameter("mod1 spacing",-1,1,0),
                  pMod1Spiral = new FloatParameter("mod1 spiral",-1,1,0),
                  pMod2Spacing = new FloatParameter("mod2 spacing",-1,1,0),
                  pMod2Spiral = new FloatParameter("mod2 spiral",-1,1,0),
                  
                  pCrawl = new FloatParameter("crawl",-4,4,0),
                  pMod1Crawl = new FloatParameter("mod1 crawl",-1,1,0),
                  pSpiralRot = new FloatParameter("spiral rot",-4,4,0),
                  pCrawlOff = new BoolParameter("crawl off",false),
                  pMod2Copies = new BoolParameter("mod2 copies",false),
                  NULL);
    }
    
    virtual void initComponentInstance(ComponentInstance *c){
        lincop *lc = new lincop();
        c->privateData = (void *)lc;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((lincop *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        Component *c = ci->component;
        lincop *lcs = (lincop *)ci->privateData;
        if(out==1){
            ci->setOutput(1,ConnectionValue::makeFloat(lcs->pos));
        } else {
            int num;
            if(ci->isInputConnected(2) && pMod2Copies->get(c))
                num = (int)(ci->getInput(2).f);
            else
                num = pCopies->get(c);
            
            if(num){
                float spiralelementrot = pSpiralRot->get(c);
                float mod1 = ci->isInputConnected(1) ?ci->getInput(1).f:0.0f;
                float mod2 = ci->isInputConnected(2) ?ci->getInput(2).f:0.0f;
                
                float spacing = pSpacing->get(c) +
                      mod1*pMod1Spacing->get(c) +
                      mod2*pMod2Spacing->get(c);
                
                float spiral = pSpiral->get(c) +
                      mod1*pMod1Spiral->get(c) +
                      mod2*pMod2Spiral->get(c);
                
                float rot = pRotate->get(c);
                float scale = pScale->get(c);
                
                if(ci->isFirstCallThisFrameForOutput(0))
                {
                    if(true) // ispaused
                    {
                        double rate = pCrawl->get(c) + pMod1Crawl->get(c)*mod1;
                        lcs->offset += rate;
                        if(lcs->offset<0.0f)lcs->offset+=1.0f;
                        if(lcs->offset>1.0f)lcs->offset-=1.0f;
                        
                        if(pCrawlOff->get(c))
                            lcs->offset = 0.0f;
                    }
                }
                
                float o = lcs->offset;
                
                
                Matrix m = Matrix::IDENTITY;
                
                float mulzerotoone = 1.0f / (float)(num+1);
                
                MatrixStack *ms = StateManager::getInstance()->getx();
                
                for(int i=0;i<num;i++)
                {
                    float x = (((float)i) + o);
                    float zerotoone = x*mulzerotoone;
                    
                    // write the pos so we can get inside other components using output 1
                    lcs->pos = x;
                    
                    x *= spacing;
                    
                    ms->push();
                    m.setTranslation(0,0,0);
                    m.setRotZ(rot + spiral*x);
                    ms->mul(&m);
                    
                    m.setScale(1,1,1);
                    m.setTranslation(x,0,0);
                    ms->mul(&m);
                    
                    m.setTranslation(0,0,0);
                    m.setRotZ(rot + spiral*x*spiralelementrot);
                    ms->mul(&m);
                    
                    m.setScale(scale,scale,scale);
                    ms->mul(&m);
                    
                    float fade;
                    
                    if(!i && o>0.0f)
                        fade = o;
                    else if(i==num-1 && o>0.0f)
                        fade = (1.0f-o);
                    else
                        fade = 1;
                    ci->setOutput(2,ConnectionValue::makeFloat(fade));
                    ci->getInput(0);
                    ci->setOutput(0,ConnectionValue::makeFlow());
                    
                    ms->pop();
                }
            }
        }
    }
    
private:
    IntParameter *pCopies;
    FloatParameter *pSpacing,*pSpiral,*pScale,*pRotate;
    FloatParameter *pMod1Spacing,*pMod1Spiral;
    FloatParameter *pMod2Spacing,*pMod2Spiral;
    
    FloatParameter *pCrawl,*pMod1Crawl,*pSpiralRot;
    BoolParameter *pCrawlOff,*pMod2Copies;
};

static LinearComponent reg;






