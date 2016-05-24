/**
 * \file
 * Brief description. Longer description.
 *
 * 
 * \author $Author$
 * \date $Date$
 */

#include "texture.h"
#include "tga.h"

TextureManager *TextureManager::inst=NULL;

Texture::Texture(QString name){
    ERRCHK;
    
    QByteArray ba = name.toLocal8Bit();
    const char *fname = ba.constData();
    
    TGAFile *file = new TGAFile(fname);
    
    if(!file->isValid())
        throw Exception().set("cannot open '%s'",fname);
    
    
    mWidth = file->getWidth();
    mHeight = file->getHeight();
    mHasAlpha = (file->getDepth()==32)?true:false;
    
    glGenTextures(1,&id);
    ERRCHK;	
    glBindTexture(GL_TEXTURE_2D,id);
    ERRCHK;
    
    if(file->getDepth()==24)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, file->getData());
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, file->getData());
    ERRCHK;
    
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);        
    delete file;
}

Texture::~Texture(){
}

void Texture::use(int sampler, int unit){
    ERRCHK;
    glActiveTexture(GL_TEXTURE0+unit); // we are modifying texture unit 'unit'
    ERRCHK;
    glBindTexture(GL_TEXTURE_2D,id); // bind the given texture into the current unit
    ERRCHK;
    glUniform1i(sampler,unit); // tell the given sampler to use that unit
    ERRCHK;
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

//    if(mHasAlpha)
//       glEnable(GL_BLEND);
//    else
//        glDisable(GL_BLEND);
   
}

Texture *TextureManager::createOrFind(QString name){
    if(textures.contains(name)){
        return textures.value(name);
    } else {
        Texture *t = new Texture(name);
        textures.insert(name,t);
        return t;
    }
}


void GLerrorcheck(const char *file,int line){
    int code = glGetError();
    if(code != GL_NO_ERROR)
        throw  Exception().set("GL error at %s:%d - 0x%x",file,line,code);
}
