/**
 * \file
 * Brief description. Longer description.
 * 
 * \author $Author$
 * \date $Date$
 */


#ifndef __EFFECT_H
#define __EFFECT_H

#include "texture.h"
#include "vertexdata.h"

class Effect {
    friend class EffectManager;
public:
    virtual bool begin(Matrix *view);
    
    void end();
    
protected:
    /// 1st stage of initialisation
    Effect(){
        mpVShader = NULL;
        mpFShader = NULL;
        vshader=0;
        fshader=0;
        program=0xffffffff;
    }
    
    /// 2nd stage - separated to avoid calling overridable methods from constructor
    Effect *init(){
        initFromFile(getFileName());
        return this;
    }
        
    virtual ~Effect();
    
    /// returns the filename for this constructor - generally a constant
    /// set up by the class. A strange way to do it, I suppose. Should really be
    /// pure, but there's a warning there.
    virtual const char *getFileName(){
        throw Exception("no filename for effect");
    }
    
    virtual void initFromFile(const char *name);
    void initFromData(const char *vertSrc,const char *fragSrc);
    
    /// effect currently in use; checked in Begin()
    static Effect *mCurEffect;
    /// use this to get attribute and uniform indices in subclasses
    virtual void getAttributes()=0;
    
    /// shader filename
    char mName[64];
    
    /// pointer to vertex shader text
    const char *mpVShader;
    
    /// pointer to fragment shader text
    const char *mpFShader;
    
    GLuint vshader,fshader,program;
    
    Matrix viewMatrix;
    
    /// used to get shader indices
    int getAttribute(const char *name);
    /// used to get shader indices
    int getUniform(const char *name);
    
    /// actually does the compile
    void compile();
    

    void uploadLights(class State *s,
                      int lc1,int ld1,
                      int lc2,int ld2,
                      int lc3,int ld3,int a,
                      int fcol,int fdist);

};







class PrelitUntexEffect : public Effect {
public:
    virtual const char *getFileName(){
        return "media/prelit_untex.shr";
    }

    
    /// set up the GL array pointers
    virtual void setArrays(PRELITVERTEX *v);
    
    /// set the material parameters
    void setMaterial(float *diffuse);
    
    /// set up the constants used per-render (like matrices)
    virtual void setWorldMatrix(Matrix *world);
    
protected:
    virtual void getAttributes();
    
    // uniform indices
    int mWorldViewProjIdx;
    int mDiffuseIdx;
    // attribute indices
    int mPosIdx;
};
        
/// This is an effect which renders textured triangles made up of PRELITVERTEX data with a single flat colour - no lighting calculations are performed.
/// The QuadBuffer and Font classes make use of this effect.

class PrelitTexEffect : public PrelitUntexEffect
{
public:
    virtual const char *getFileName(){
        return "media/prelit_tex.shr";
    }

    /// set up the GL array pointers
    virtual void setArrays(PRELITVERTEX *v);
    
    /// set the material parameters
    void setMaterial(float *diffuse,class Texture *texture);

protected:
    virtual void getAttributes();
    int mTexCoordIdx,mSamplerIdx;
    
};

class MeshTexEffect : public PrelitTexEffect
{
public:
    virtual const char *getFileName(){
        return "media/mesh.shr";
    }

    /// set up the GL array pointers (in this case, just offsets)
    virtual void setArrays();
    
    /// set up the constants used per-render (like matrices)
    virtual void setWorldMatrix(Matrix *world);
    
    virtual bool begin(Matrix *view);
    
protected:
    
    virtual void getAttributes();
    
protected:
    int LightCol1Idx;
    int LightCol2Idx;
    int LightCol3Idx;
    int LightDir1Idx;
    int LightDir2Idx;
    int LightDir3Idx;
    int AmbientColIdx;
    int FogColIdx,FogDistIdx;
    int mNormalMatIdx,mNormIdx;
    
};
    
class MeshUntexEffect : public PrelitUntexEffect
{
public:
    virtual const char *getFileName(){
        return "media/mesh_untex.shr";
    }

    /// set up the GL array pointers (in this case, just offsets)
    virtual void setArrays();
    
    /// set up the constants used per-render (like matrices)
    virtual void setWorldMatrix(Matrix *world);
    
    virtual bool begin(Matrix *view);
    
    
protected:
    
    virtual void getAttributes();
    
protected:
    int LightCol1Idx;
    int LightCol2Idx;
    int LightCol3Idx;
    int LightDir1Idx;
    int LightDir2Idx;
    int LightDir3Idx;
    int FogColIdx,FogDistIdx;
    int AmbientColIdx;
    int mNormalMatIdx,mNormIdx;
    
};



/// effect manager singleton - acts as a manager and "factory" (well, warehouse..)

class EffectManager {
    EffectManager(){
        prelitUntex = new PrelitUntexEffect();
        prelitTex = new PrelitTexEffect();
        meshTex = new MeshTexEffect();
        meshUntex = new MeshUntexEffect();
        
        prelitUntex->init();
        prelitTex->init();
        meshUntex->init();
        meshTex->init();
    }
    
    static EffectManager *instance;
    
public:
    static EffectManager *getInstance(){
        if(instance==NULL)
            instance = new EffectManager();
        return instance;
    }
    
    PrelitUntexEffect *prelitUntex;
    PrelitTexEffect *prelitTex;
    MeshUntexEffect *meshUntex;
    MeshTexEffect *meshTex;
};
    
    
        


#endif /* __EFFECT_H */
