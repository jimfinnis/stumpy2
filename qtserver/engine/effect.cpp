// -!- C++ -!- //////////////////////////////////////////////////////////////
//
//  			Copyright 2010 Broadsword Games.
//			      All Rights Reserved
//
//
//  System        : 
//  Module        : 
//  Object Name   : $RCSfile$
//  Revision      : $Revision$
//  Date          : $Date$
//  Author        : $Author$
//  Created By    : Jim Finnis
//  Created       : Mon May 10 15:57:47 2010
//  Last Modified : <160524.1300>
//
//  Description	
//
//  Notes
//
//  History
//	
/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2010 Broadsword Games.
// 
//  All Rights Reserved.
// 
// This  document  may  not, in  whole  or in  part, be  copied,  photocopied,
// reproduced,  translated,  or  reduced to any  electronic  medium or machine
// readable form without prior written consent from Broadsword Games.
//
//////////////////////////////////////////////////////////////////////////////

#include "effect.h"
#include "state.h"
#include <QFile>

StateManager *StateManager::instance = NULL;
EffectManager *EffectManager::instance = NULL;

/**
 * Effect manager initialisation - shader loading
 */

EffectManager::EffectManager(){
//    prelitUntex = new Effect("media/prelit_untex.shr",0);
    //    prelitTex = new Effect("media/prelit_tex.shr",0);
    prelitUntex =  NULL;
    prelitTex = NULL;
    
    meshTex = new Effect("media/mesh.shr",
                         EDA_POS|EDA_NORM|
                         EDU_WORLDVIEWPROJ|EDU_NORMMAT|EDU_DIFFUSECOL|
                         EDU_DIFFLIGHTS|EDU_AMBLIGHT|EDU_FOG|
                         EDA_TEXCOORDS|EDU_SAMPLER);
    
    meshUntex = new Effect("media/mesh_untex.shr",
                           EDA_POS|EDA_NORM|
                           EDU_WORLDVIEWPROJ|EDU_NORMMAT|EDU_DIFFUSECOL|
                           EDU_DIFFLIGHTS|EDU_AMBLIGHT|EDU_FOG);
                           
    envMapTex = new Effect("media/envmap.shr",
                           EDA_POS|EDA_NORM|EDA_TEXCOORDS|
                           EDU_WORLDVIEWPROJ|EDU_NORMMAT|EDU_DIFFUSECOL|
                           EDU_DIFFLIGHTS|EDU_AMBLIGHT|
                           EDU_SAMPLER|EDU_WORLDVIEW|EDU_FOG|
                           EDU_SAMPLER2|EDU_DIFFUSE2);
    
    // separate to avoid calling overridable stuff from ctor.
///    prelitUntex->init();
//    prelitTex->init();
    meshUntex->init();
    meshTex->init();
    envMapTex->init();
}


/*****************************************************************************
 * 
 * 
 * 
 * Effects (i.e. shaders and programs)
 * 
 * 
 * 
 ****************************************************************************/

static int loadShader(GLenum type,const char *src)
{
    //    printf("READY TO COMPILE\n%s",src);
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);
    ERRCHK;
    if(!shader)
        return 0;
    glShaderSource(shader,1,&src,NULL);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
    if(!compiled){
        GLint infolen;
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infolen);
        char *log = (char*)"??";
        if(infolen>1){
            log = (char *)malloc(infolen);
            glGetShaderInfoLog(shader,infolen,NULL,log);
            printf("error compiling shader:\n%s\n",log);
        }
        glDeleteShader(shader);
        throw Exception().set("cannot compile shader: %s",log);
    }
    return shader;
}

void Effect::compile(){
    printf("Compiling shader %s\n",mName);
    vshader = loadShader(GL_VERTEX_SHADER,mpVShader);
    ERRCHK;
    fshader = loadShader(GL_FRAGMENT_SHADER,mpFShader);
    ERRCHK;
    if(mpGShader){
        printf("%s\n",mpGShader);
        gshader = loadShader(GL_GEOMETRY_SHADER,mpGShader);
        ERRCHK;
    }
    
    program = glCreateProgram();
    if(!program)
        throw Exception().set("cannot create program for shader '%s'",mName);
    glAttachShader(program,vshader);
    ERRCHK;
    if(mpGShader){
        glAttachShader(program,gshader);
        ERRCHK;
    }
    glAttachShader(program,fshader);
    ERRCHK;
    
    
    glLinkProgram(program);
    ERRCHK;
    printf("Get attr for %s\n",mName);
    getAttributes(); // written for each effect
    printf("Get attr done\n");
    GLint linked;
    glGetProgramiv(program,GL_LINK_STATUS,&linked);
    ERRCHK;
    if(!linked){
        GLint infolen;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH,&infolen);
        char *log = (char *)"??";
        if(infolen>1){
            log = (char *)malloc(infolen);
            glGetProgramInfoLog(program,infolen,NULL,log);
            printf("error linking shaders:\n%s\n",log);
        }
        glDeleteProgram(program);
        throw Exception().set("cannot link program %s: %s",mName,log);
    }
    
}

class growbuf
{
    static const int startsize = 256;
    static const int growsize = 256;
    
public:
    
    growbuf()
    {
        buf = (char *)malloc(startsize);
        strlen = 0;
        buflen = startsize;
    }
    
    void add(char c)
    {
        if(strlen==buflen)
        {
            int newbuflen = buflen+growsize;
            char *newbuf = (char *)malloc(newbuflen);
            memcpy(newbuf,buf,buflen);
            free(buf);
            
            buflen = newbuflen;
            buf = newbuf;
        }
        buf[strlen++]=c;
    }
    
    char *endandreturn()
    {
        add(0);
        return buf;
    }
    
    void include(const char *fname)
    {
        QFile file(fname);
        if(!file.open(QIODevice::ReadOnly))
            throw Exception().set("cannot open file %s",fname);
        QByteArray b = file.readAll();
        if(b.isEmpty() || b.isNull())
            throw Exception().set("cannot read file %s",fname);
        char *data = b.data();
        uint32_t size = b.size();
        file.close();
        
        char *q = data;
        for(uint32_t i=0;i<size;i++)
            add(*q++);
    }
    
private:
    char *buf;
    int strlen,buflen;
};

static char *handleInclusion(char *in)
{
    growbuf buf;
    
    for(char *q = in;*q;q++)
    {
        if(*q == '#' && !strncmp(q+1,"include",7))
        {
            q+=8;
            while(*q != '<')q++;
            q++;
            char *fnend = q;
            while(*fnend != '>')fnend++;
            char fname[128];
            memcpy(fname,q,fnend-q);
            fname[fnend-q]=0;
            q=fnend+1;
            buf.include(fname);
        }
        else
            buf.add(*q);
    }
    return buf.endandreturn();
}

void Effect::initFromFile(){
    // there are two shaders, but we're going to put them into a single file
    // here. They are separated by a "##" line. We read the data into a single buffer,
    // then walk through it setting up pointers and adding nulls.    
    
    QFile file(mName);
    if(!file.open(QIODevice::ReadOnly))
        throw Exception().set("cannot open file %s",mName);
    QByteArray b = file.readAll();
    if(b.isEmpty() || b.isNull())
        throw Exception().set("cannot read file %s",mName);
    b.append((char)0);
    char *str = b.data();
    file.close();
    
    
    char *vshad,*fshad,*gshad=NULL;
    
    for(char *q=str;*q;q++)
    {
        if(*q=='%' && q[1]=='%')
        {
            // mark end of previous element
            *q = 0;
            // and go forward
            q+=2;
            if(!strncmp(q,"vertex",6))
            {
                q+=6;
                vshad = q;
            }
            else if(!strncmp(q,"fragment",8))
            {
                q+=8;
                fshad = q;
            }
            else if(!strncmp(q,"geometry",8))
            {
                q+=8;
                gshad = q;
            }
        }
    }
    
    if(!fshad)
        throw Exception().set("fragment shader missing in %s",mName);
    if(!vshad)
        throw Exception().set("vertex shader missing in %s",mName);
    
    mpVShader = handleInclusion(vshad);
    mpFShader = handleInclusion(fshad);
    if(gshad)
        mpGShader = handleInclusion(gshad);
    else
        mpGShader = NULL;
    
    compile();
}

void Effect::initFromData(const char *vshad,const char *fshad){
    mpVShader = strdup(vshad);
    mpFShader = strdup(fshad);
    compile();
}      


Effect::~Effect(){
    if(program)
        glDeleteProgram(program);
    if(vshader)
        glDeleteShader(vshader);
    if(fshader)
        glDeleteShader(fshader);
    if(gshader)
        glDeleteShader(gshader);
    if(mpVShader)
        free((void *)mpVShader);
    if(mpFShader)
        free((void *)mpFShader);
    if(mpGShader)
        free((void *)mpGShader);
}

Effect *Effect::mCurEffect=NULL;

bool Effect::begin(){
    if(mCurEffect != this)
    {
        glUseProgram(program);
        ERRCHK;
        setUniforms();
        mCurEffect = this;
        return true;
    }
    else
        return false;
}

void Effect::end(){
    glUseProgram(0);
    mCurEffect=NULL;
}

int Effect::getAttribute(const char *name){
    int i = glGetAttribLocation(program,name);
    if(i<0)
        throw Exception().set("attribute not found: %s",name);
    //    printf("attr %s: %d\n",name,i);
    return i;
}

int Effect::getUniform(const char *name)
{
    printf("%s\n",name);
    int i = glGetUniformLocation(program,name);
    if(i<0)
        throw Exception().set("uniform not found: %s",name);
    return i;
}

/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void Effect::getAttributes(){
    if(has(EDA_POS))
        mPosIdx = getAttribute("aPosition");
    if(has(EDU_WORLDVIEWPROJ))
        mWorldViewProjIdx = getUniform("matWorldViewProj");
    if(has(EDU_DIFFUSECOL))
        mDiffuseIdx = getUniform("colDiffuse");
    if(has(EDA_TEXCOORDS))
        mTexCoordIdx = getAttribute("aTexCoords");
    if(has(EDU_SAMPLER))
        mSamplerIdx = getUniform("sTex");
    if(has(EDU_NORMMAT))
        mNormalMatIdx = getUniform("matNormal");
    if(has(EDA_NORM))
        mNormIdx = getAttribute("aNormal");
    
    if(has(EDU_DIFFLIGHTS)){
        LightCol1Idx = getUniform("uLight1Col");
        LightCol2Idx = getUniform("uLight2Col");
        LightCol3Idx = getUniform("uLight3Col");
        LightDir1Idx = getUniform("uLight1Dir");
        LightDir2Idx = getUniform("uLight2Dir");
        LightDir3Idx = getUniform("uLight3Dir");
    }
    if(has(EDU_AMBLIGHT))
        AmbientColIdx = getUniform("uAmbient");
    if(has(EDU_FOG)){
        FogColIdx = getUniform("uFogCol");
        FogDistIdx = getUniform("uFogDist");
    }
    if(has(EDU_DIFFUSE2)){
        mDiffuse2Idx = getUniform("colDiffuse2");
    }
    if(has(EDU_SAMPLER2)){
        mSampler2Idx = getUniform("sTex2");
    }
    if(has(EDU_WORLDVIEW))
        mWorldViewIdx = getUniform("matWorldView");
}

void Effect::setWorldMatrix(Matrix *world){
    Matrix modelview,worldviewproj;
    
    State *s = StateManager::getInstance()->get();
    
    // these have to be FULL multiplies!
    
    modelview.mulF(*world,s->view);
    worldviewproj.mulF(modelview,Matrix::Projection);
    
    if(has(EDU_WORLDVIEWPROJ))
        glUniformMatrix4fv(mWorldViewProjIdx,1,
                       GL_FALSE,(float *)&worldviewproj);
    
    if(has(EDU_WORLDVIEW)){
        glUniformMatrix4fv(mWorldViewIdx,1,
                           GL_FALSE,(float *)&modelview);
    
    }
    
    // set up the normal matrix
    
    if(has(EDU_NORMMAT)){
        Matrix m,m2;
        m=modelview;
        m.invert(modelview);
        float arr[9];
        m.copyRotToFloatArrayTrans(arr);
        glUniformMatrix3fv(mNormalMatIdx,1,GL_FALSE,arr);
    }
    
    if(has(EDU_DIFFLIGHTS)){
        glUniform4fv(LightCol1Idx,1,(float *)&s->light.col[0]);
        glUniform4fv(LightCol2Idx,1,(float *)&s->light.col[1]);
        glUniform4fv(LightCol3Idx,1,(float *)&s->light.col[2]);
    
        // transform light into view space
    
        Vector v;
        Matrix m = s->view;
        m.setTranslation(0,0,0);
    
        v.transform(s->light.dir[0],m);
        glUniform3fv(LightDir1Idx,1,(float *)&v);
    
        v.transform(s->light.dir[1],m);
        glUniform3fv(LightDir2Idx,1,(float *)&v);
    
        v.transform(s->light.dir[2],m);
        glUniform3fv(LightDir3Idx,1,(float *)&v);
    }
}

void Effect::setUniforms(){
    State *s = StateManager::getInstance()->get();
    
    if(has(EDU_AMBLIGHT))
        glUniform4fv(AmbientColIdx,1,(float *)&s->light.ambient);
    
    if(has(EDU_FOG)){
        glUniform4fv(FogColIdx,1,(float *)&s->fog.color);
        glUniform2fv(FogDistIdx,1,(float *)&s->fog.neardist);
    }
    if(has(EDU_DIFFUSE2)){
        glUniform4fv(mDiffuse2Idx,1,(float*)&s->diffuse2);
        ERRCHK;
    }
    if(has(EDU_SAMPLER2)){
        // tell sampler to use unit 1 with this texture
        s->texture2->use(mSampler2Idx,1);
        ERRCHK;
    }
}    

void Effect::setMaterial(float *diffuse,class Texture *texture)
{
    if(has(EDU_DIFFUSECOL)){
        glUniform4fv(mDiffuseIdx,1,diffuse);
        ERRCHK;
    }
    
    if(has(EDU_SAMPLER) && texture){
        texture->use(mSamplerIdx,0); // tell sampler to use unit 0, with the given texture
        ERRCHK;
    }
}


/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void Effect::setArrayPointersPrelit(PRELITVERTEX *v)
{
    float *p = (float *)v;
    // sets array *values*
    if(has(EDA_POS)){
        glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(PRELITVERTEX),p); // attr, size, type, norm, stride, ptr
        glEnableVertexAttribArray(mPosIdx);
    }
    
    if(has(EDA_TEXCOORDS)){
        glVertexAttribPointer(mTexCoordIdx,2,GL_FLOAT,GL_FALSE,sizeof(PRELITVERTEX),p+3); // attr, size, type, norm, stride, ptr
        glEnableVertexAttribArray(mTexCoordIdx);
    }
}


/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void Effect::setArrayOffsetsUnlit()
{
    // sets array *offsets* 
    if(has(EDA_POS)){
        glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,x));
        glEnableVertexAttribArray(mPosIdx);
    }
    if(has(EDA_NORM)){
        glVertexAttribPointer(mNormIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,nx));
        glEnableVertexAttribArray(mNormIdx);
    }
    if(has(EDA_TEXCOORDS)){
        glVertexAttribPointer(mTexCoordIdx,2,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,u));
        glEnableVertexAttribArray(mTexCoordIdx);
    }
}

