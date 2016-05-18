/* -*- C -*- ****************************************************************
 *
 *  			Copyright 2010 Broadsword Games.
 *			      All Rights Reserved
 *
 *
 *  System        : 
 *  Module        : 
 *  Object Name   : $RCSfile$
 *  Revision      : $Revision$
 *  Date          : $Date$
 *  Author        : $Author$
 *  Created By    : Jim Finnis
 *  Created       : Tue May 4 14:27:17 2010
 *  Last Modified : <160518.2106>
 *
 *  Description	
 *
 *  Notes
 *
 *  History
 *	
 ****************************************************************************
 *
 *  Copyright (c) 2010 Broadsword Games.
 * 
 *  All Rights Reserved.
 * 
 * This  document  may  not, in  whole  or in  part, be  copied,  photocopied,
 * reproduced,  translated,  or  reduced to any  electronic  medium or machine
 * readable form without prior written consent from Broadsword Games.
 *
 ****************************************************************************/

#ifndef __MESH_H
#define __MESH_H

#include "maths.h"
#include "texture.h"
#include "renderable.h"

/// a wrapper around a Mesh loaded from an X file.
/// Initialise by calling Init(directory,meshname) where meshname is 
/// an X file inside the directory. The textures should be in the same
/// directory, and the X file should refer to them without any directory
/// components to their filenames. Render with Render() - the Mesh Effect
/// in the Application structure will be used.
class Mesh : public Renderable
{
public:
    
    /// Given a directory, load a given .x file and a given set of
    /// textures from it.
    
    Mesh(const char *dir,const char *name);
    
    /// release the mesh and the textures
    virtual ~Mesh();
    
    /// draw me 
    virtual void render(Matrix *view,Matrix *world);
    
    /// set effect to render textured submeshes with
    void setTexEffect(class MeshTexEffect *e)
    {
        mTexEffect = e;
    }
    /// set effect to render untextured submeshes with
    void setUntexEffect(class MeshUntexEffect *e)
    {
        mUntexEffect = e;
    }
    
    /// used for batch rendering of many identical meshes. This binds
    /// the vertex and index buffers of the nth SingleMesh. Assumes there's
    /// only one material in it!
    
    void bindBuffersForBatch(int n);
    
    /// used for batch rendering - set the materials for SingleMesh n's first material. Will use
    /// the appropriate effect for textured or untextured.
    void setMaterialsForBatch(int n);
    
    /// issue a draw command for the nth submesh, assuming that all
    /// uniforms have been set and buffers bound. It will assume that
    /// there's only one material, the uniforms for which have been set.
    void drawForBatch(int n);
    
    void doparsefailed(int e); // public so SingleMesh can see it
    
    
    
protected:
    void parseFrame();
    void parseMesh();
    
    
    /// actually loads the data
    void reset();
    /// actually deletes the data
    void lost();
    
    // render textured components - possibly replacing all textures
    // with another one
    virtual void renderTex(Matrix *view,Matrix *world,Texture *overrideTex=NULL);
    // render untextured components
    virtual void renderUntex(Matrix *view,Matrix *world);
    
    /// these are the actual meshes (a Mesh can be made up of several submeshes within the xfile)
    
    struct SingleMesh *mSubMeshes[16];
    int mNumSubMeshes; 
    MeshTexEffect *mTexEffect; // if null, use default effects!
    MeshUntexEffect *mUntexEffect; // if null, use default effects!
    
    bool hasuntex; // does it have textured materials?
    bool hastex; // does it have untextured materials?    
    bool hasalpha; // true if it has alpha'd textures
    const char *mName;
    const char *mDir;
    
};





#endif /* __MESH_H */
