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
#include "lodepng.h"

#include <strings.h>
#include <vector>
#include <dirent.h>

TextureManager *TextureManager::inst=NULL;

Texture::Texture(QString n) {
    valid=false;
    name=NULL;
    ERRCHK;
    QByteArray ba = n.toLocal8Bit();
    const char *fname = ba.constData();
    
    if(strlen(fname)<3)
        throw Exception().set("silly texture file name '%s'",fname);
    
    const char *dot = rindex(fname,'.');
    if(!dot)
        throw Exception().set("silly texture file name '%s'",fname);
    
    const char *ext = dot+1;
    
    
    const unsigned char *bytes;
    std::vector<unsigned char> img;
    int depth;
    TGAFile *file=NULL;
    if(!strcasecmp("tga",ext)){
        file = new TGAFile(fname);
        
        if(!file->isValid())
            throw Exception().set("cannot open '%s'",fname);
        
        
        mWidth = file->getWidth();
        mHeight = file->getHeight();
        mHasAlpha = (file->getDepth()==32)?true:false;
        bytes = (const unsigned char *)file->getData();
        depth = file->getDepth();
    } else if(!strcasecmp("jpg",ext) || !strcasecmp("jpeg",ext)){
        printf("jpg not supported, oops : %s\n",fname);
        return;
    } else {
        unsigned int err = lodepng::decode(img,mWidth,mHeight,fname);
        if(err)
            throw Exception().set("cannot open '%s': %s",fname,
                                  lodepng_error_text(err));
        bytes = &img[0]; // get data ptr
        depth = 32;    
    }
    glGenTextures(1,&id);
    ERRCHK;	
    glBindTexture(GL_TEXTURE_2D,id);
    ERRCHK;
    
    if(depth==24)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    ERRCHK;
    
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    //            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //            glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);        
    if(file)delete file;
    name = strdup(fname);
    valid=true;
}

Texture::~Texture(){
    if(name)free((void *)name);
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
        if(t->valid){
            textures.insert(name,t);
            return t;
        } else {
            delete t;
            return NULL;
        }
    }
}


void GLerrorcheck(const char *file,int line){
    int code = glGetError();
    if(code != GL_NO_ERROR)
        throw  Exception().set("GL error at %s:%d - 0x%x",file,line,code);
}

void TextureManager::loadSet(const char *dirname,
                             std::vector<Texture *>&vec){
    DIR *dir = opendir(dirname);
    if(!dir)
        throw Exception().set("cannot open directory '%s'",dirname);
    
    vec.clear();
    while(dirent *ent = readdir(dir)){
        const char *name = ent->d_name;
        if(strlen(name)>3){
            const char *ext = name+(strlen(name)-3);
            if(!strcasecmp(ext,"png") || !strcasecmp(ext,"tga")){
                // throws on failure
                QString qname(dirname);
                qname+="/"+QString(name);
                Texture *t = createOrFind(qname);
                vec.push_back(t);
            }
        }
    }
    if(!vec.size())
        throw Exception().set("no textures found in '%s'",dirname);
}
