/**
 * \file
 * Brief description. Longer description.
 * 
 * \author $Author$
 * \date $Date$
 */


#ifndef __RENDERABLE_H
#define __RENDERABLE_H

#include "maths.h"

/// used for renderable objects
class Renderable{
public:
    virtual void render(Matrix *view,Matrix *world) = 0;
};


#endif /* __RENDERABLE_H */
