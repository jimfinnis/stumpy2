/**
 * @file obj.h
 * @brief A renderable built from an OBJ file, loaded using
 * TinyObjLoader.
 *
 */

#ifndef __OBJ_H
#define __OBJ_H

#include "maths.h"
#include "texture.h"
#include "renderable.h"

#include <vector>

struct Transition{
    int start,count,matidx;
};

class ObjMesh : public Renderable
{
    struct Material *mats;
    
    GLuint buffers[2];
    std::vector<Transition> transitions;
    
    void renderTex(Matrix *world);
    void renderUntex(Matrix *world);
    
public:
    ObjMesh(const char *dir,const char *name);
    virtual ~ObjMesh();
    
    // standard render method
    virtual void render(Matrix *world);
};


#endif /* __OBJ_H */
