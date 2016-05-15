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
//  Last Modified : <160515.1313>
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
    getAttributes(); // written for each effect
    
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

void Effect::initFromFile(const char *name){
    // there are two shaders, but we're going to put them into a single file
    // here. They are separated by a "##" line. We read the data into a single buffer,
    // then walk through it setting up pointers and adding nulls.    
    
    strncpy(mName,name,64);
    
    QFile file(mName);
    if(!file.open(QIODevice::ReadOnly))
        throw Exception().set("cannot open file %s",name);
    QByteArray b = file.readAll();
    if(b.isEmpty() || b.isNull())
        throw Exception().set("cannot read file %s",name);
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

bool Effect::begin(Matrix *view){
    viewMatrix = *view;
    
    if(mCurEffect != this)
    {
        glUseProgram(program);
        
        ERRCHK;
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
    int i = glGetUniformLocation(program,name);
    if(i<0)
        throw Exception().set("uniform not found: %s",name);
    return i;
}

// upload all lighting states into a shader
// lc.. ld.. are the light colour and direction uniform indices. The ambient index is a.
void Effect::uploadLights(State *s,int lc1,int ld1,
                          int lc2,int ld2,
                          int lc3,int ld3,int a,
                          int fcol,int fdist){
    
    glUniform4fv(lc1,1,(float *)&s->light.col[0]);
    glUniform4fv(lc2,1,(float *)&s->light.col[1]);
    glUniform4fv(lc3,1,(float *)&s->light.col[2]);
    
    // transform light into eye space - not sure if this is right.
    
    Vector v;
    Matrix m = viewMatrix;
    m.setTranslation(0,0,0);
    
    v.transform(s->light.dir[0],m);
    glUniform3fv(ld1,1,(float *)&v);
    
//    v.dump();
    
    v.transform(s->light.dir[1],m);
    glUniform3fv(ld2,1,(float *)&v);
    
    v.transform(s->light.dir[2],m);
    glUniform3fv(ld3,1,(float *)&v);
    
    glUniform4fv(a,1,(float *)&s->light.ambient);
    
    glUniform4fv(fcol,1,(float *)&s->fog.color);
    glUniform2fv(fdist,1,(float *)&s->fog.neardist);
}

/*****************************************************************************
 * 
 * General purpose helpers
 * 
 ****************************************************************************/

// given the indices of the WorldViewProjection and WorldRot matrices in the shader,
// set them from the matrices passed in.
static void setMeshMatrices(Matrix *view,Matrix *world,int wvpidx,int nmidx)
{
    Matrix modelview,worldviewproj;
    
    // these have to be FULL multiplies!
    
    modelview.mulF(*world,*view);
    worldviewproj.mulF(modelview,Matrix::Projection);
    
    glUniformMatrix4fv(wvpidx,1,GL_FALSE,(float *)&worldviewproj);
    
    // set up the normal matrix
    
    Matrix m,m2;
    m=modelview;
    m.invert(modelview);
    float arr[9];
    m.copyRotToFloatArrayTrans(arr);
    
//    modelview.dump();
    
    // upload. 
    glUniformMatrix3fv(nmidx,1,GL_FALSE,arr);
}



/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void PrelitUntexEffect::getAttributes()
{
    mPosIdx = getAttribute("aPosition");
    mWorldViewProjIdx = getUniform("matWorldViewProj");
    mDiffuseIdx = getUniform("colDiffuse");
}

void PrelitUntexEffect::setArrays(PRELITVERTEX *v)
{
    float *p = (float *)v;
    // positions
    glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(PRELITVERTEX),p); // attr, size, type, norm, stride, ptr
    ERRCHK;
    // we ignore texture coords
    
    glEnableVertexAttribArray(mPosIdx);
    ERRCHK;
}

void PrelitUntexEffect::setWorldMatrix(Matrix *world)
{
    Matrix worldviewproj= (*world) * viewMatrix * Matrix::Projection;
    glUniformMatrix4fv(mWorldViewProjIdx,1,0,(float *)&worldviewproj);
}

void PrelitUntexEffect::setMaterial(float *diffuse)
{
    //glDisable(GL_BLEND);
    glUniform4fv(mDiffuseIdx,1,diffuse);
}

/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void PrelitTexEffect::getAttributes()
{
    PrelitUntexEffect::getAttributes(); // inherited stuff
    
    mTexCoordIdx = getAttribute("aTexCoords");
    mSamplerIdx = getUniform("sTex");
}

void PrelitTexEffect::setArrays(PRELITVERTEX *v)
{
    float *p = (float *)v;
    // positions
    glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(PRELITVERTEX),p); // attr, size, type, norm, stride, ptr
    glVertexAttribPointer(mTexCoordIdx,2,GL_FLOAT,GL_FALSE,sizeof(PRELITVERTEX),p+3); // attr, size, type, norm, stride, ptr
    
    glEnableVertexAttribArray(mPosIdx);
    glEnableVertexAttribArray(mTexCoordIdx);
}

void PrelitTexEffect::setMaterial(float *diffuse,class Texture *texture)
{
    glUniform4fv(mDiffuseIdx,1,diffuse);
    ERRCHK;
    
    texture->use(mSamplerIdx,0); // tell sampler to use unit 0, with the given texture
    ERRCHK;
}


/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void MeshTexEffect::getAttributes()
{
    PrelitTexEffect::getAttributes(); // inherited stuff
    
    mNormalMatIdx = getUniform("matNormal");
    mNormIdx = getAttribute("aNormal");
    
    LightCol1Idx = getUniform("uLight1Col");
    LightCol2Idx = getUniform("uLight2Col");
    LightCol3Idx = getUniform("uLight3Col");
    LightDir1Idx = getUniform("uLight1Dir");
    LightDir2Idx = getUniform("uLight2Dir");
    LightDir3Idx = getUniform("uLight3Dir");
    AmbientColIdx = getUniform("uAmbient");
    FogColIdx = getUniform("uFogCol");
    FogDistIdx = getUniform("uFogDist");
}

void MeshTexEffect::setArrays()
{
    glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,x));
    glVertexAttribPointer(mNormIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,nx));
    glVertexAttribPointer(mTexCoordIdx,2,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,u));
    
    glEnableVertexAttribArray(mPosIdx);
    glEnableVertexAttribArray(mNormIdx);
    glEnableVertexAttribArray(mTexCoordIdx);
}

void MeshTexEffect::setWorldMatrix(Matrix *world)
{
    setMeshMatrices(&viewMatrix,world,mWorldViewProjIdx,mNormalMatIdx);
}

bool MeshTexEffect::begin(Matrix *v)
{
    bool b;
    if((b=Effect::begin(v)))
    {
        uploadLights(StateManager::getInstance()->get(),
                     LightCol1Idx,LightDir1Idx,
                     LightCol2Idx,LightDir2Idx,
                     LightCol3Idx,LightDir3Idx,
                     AmbientColIdx,FogColIdx,FogDistIdx);
    }
    return b;
}

/*****************************************************************************
 * 
 * 
 * 
 ****************************************************************************/

void MeshUntexEffect::getAttributes()
{
    PrelitUntexEffect::getAttributes(); // inherited stuff
    
    mNormalMatIdx = getUniform("matNormal");
    mNormIdx = getAttribute("aNormal");
    
    LightCol1Idx = getUniform("uLight1Col");
    LightCol2Idx = getUniform("uLight2Col");
    LightCol3Idx = getUniform("uLight3Col");
    LightDir1Idx = getUniform("uLight1Dir");
    LightDir2Idx = getUniform("uLight2Dir");
    LightDir3Idx = getUniform("uLight3Dir");
    FogColIdx = getUniform("uFogCol");
    FogDistIdx = getUniform("uFogDist");
    AmbientColIdx = getUniform("uAmbient");
}

void MeshUntexEffect::setArrays()
{
    glVertexAttribPointer(mPosIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,x));
    glVertexAttribPointer(mNormIdx,3,GL_FLOAT,GL_FALSE,sizeof(UNLITVERTEX),(const void *)offsetof(UNLITVERTEX,nx));
    
    glEnableVertexAttribArray(mPosIdx);
    glEnableVertexAttribArray(mNormIdx);
}

void MeshUntexEffect::setWorldMatrix(Matrix *world)
{
    setMeshMatrices(&viewMatrix,world,mWorldViewProjIdx,mNormalMatIdx);
}

bool MeshUntexEffect::begin(Matrix *v)
{
    bool b;
    if((b=Effect::begin(v)))
    {
        uploadLights(StateManager::getInstance()->get(),
                     LightCol1Idx,LightDir1Idx,
                     LightCol2Idx,LightDir2Idx,
                     LightCol3Idx,LightDir3Idx,
                     AmbientColIdx,FogColIdx,FogDistIdx);
    }
    return b;
}
