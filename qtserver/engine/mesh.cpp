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
//  Created       : Tue May 4 14:28:42 2010
//  Last Modified : <160515.1312>
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
#include "tokeniser.h"
#include "mesh.h"
#include <malloc.h>
#include <unistd.h>
#include <QFile>

inline void *memalign(__attribute__((unused)) size_t align,size_t size)
{
    //    return _aligned_malloc(size,align);
    return malloc(size);
}

inline void alignedFree(void *p){
    free(p);
}

struct triple
{
    float x,y,z;
    void normalise()
    {
        float mr = sqrtf(x*x+y*y+z*z);
        if(mr>0.000001f)
        {
            mr = 1.0f/mr;
            x *= mr;
            y *= mr;
            z *= mr;
        }
    }
};

struct uv
{
    float u,v;
};


const float UNLITVERTEX::VERTEXEPSILON=0.001f;
const float UNLITVERTEX::NORMALEPSILON=0.00f;
const float UNLITVERTEX::UVEPSILON=0.01f;

struct MeshMaterial
{
    Vector diffuse;
    Texture *tex;
    void setDefault()
    {
        diffuse.r = 1;
        diffuse.g = 1;
        diffuse.b = 1;
        diffuse.a = 1;
        tex = NULL;
    }
};

struct MeshMaterialBlock
{
    int matidx,start,count;
};



/// a Mesh object can consist of several actual meshes, which are these objects.
struct SingleMesh
{
    Matrix xform;
    void parseMesh();
    void build();
    
    SingleMesh()
    {
        hasuntex = hastex = false;
    }
    
    ~SingleMesh()
    {
        delete [] mats;
        delete [] matblocks;
        alignedFree(indices);
        alignedFree(vertices);
    }
    
    void cleanUp()
    {
        // remove temporary data
        delete [] vertidxs;
        delete [] normidxs;
        delete [] verts;
        delete [] matidxs;
    }
    
    void parseMaterialList();
    void parseMeshNormals();
    void parseMeshVertexColors();
    void parseMeshTextureCoords();
    void parseVertDups();
    void parseMaterial(MeshMaterial *mat);
    
    // render textured components
    void renderTex(MeshTexEffect *eff);
    // render untextured components
    void renderUntex(MeshUntexEffect *eff);
    
    bool hasuntex; // does it have textured materials?
    bool hastex; // does it have untextured materials?    
    
    int indsperface; // 3 or 4
    int outputindicesperface; // 3 or 6 - ES doesn't do quads, so have to expand.
    int numverts;
    
    // generally temporary data that can be deleted after Build()
    
    triple *verts; // numverts vertices
    uv *uvs;	// numverts uvs
    int *vertidxs; // numfaces*indsperface indices into vertex buffer
    
    int numnorms;
    triple *norms; // numnorms normals
    int *normidxs; // numfaces*indsperface indices into normal buffer
    
    int numfaces;
    int *matidxs; // numfaces material indices
    
    int nummats;
    MeshMaterial *mats; // materials
    
    // open GL stuff created by Build()
    
    static const int VERTEXBUFFER=0;
    static const int INDEXBUFFER=1;
    
    GLuint buffers[2];
    unsigned short *indices;
    UNLITVERTEX *vertices;
    int vertexcount;
    MeshMaterialBlock *matblocks;
    int matblockcount;
};

void Mesh::bindBuffersForBatch(int n)
{
    SingleMesh *msh = mSubMeshes[n];
    glBindBuffer(GL_ARRAY_BUFFER,msh->buffers[SingleMesh::VERTEXBUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,msh->buffers[SingleMesh::INDEXBUFFER]);
}

void Mesh::setMaterialsForBatch(int n)
{
/*    
    SingleMesh *msh = mSubMeshes[n];
    MeshMaterialBlock *b = msh->matblocks+0;
    MeshMaterial *m = msh->mats + b->matidx;
    if(m->tex)
    {
        MeshTexEffect *eff = mTexEffect?mTexEffect:&MeshTexEffect::defaultEffect;
        eff->setMaterial((float*)&m->diffuse,m->tex);
    }
    else
    {
        MeshUntexEffect *eff = mUntexEffect?mUntexEffect:MeshUntexEffect::defaultEffect;
        eff->setMaterial((float*)&m->diffuse);
   }
 */
}

void Mesh::drawForBatch(int n)
{
    SingleMesh *msh = mSubMeshes[n];
    MeshMaterialBlock *b = msh->matblocks+0;
    
    glDrawElements(GL_TRIANGLES,b->count,GL_UNSIGNED_SHORT,(void *)(b->start*sizeof(unsigned short)));
}


Mesh::Mesh(const char *dir, const char *name)
{
    mTexEffect = NULL;
    mUntexEffect = NULL;
    hasuntex = hastex = hasalpha = false;
    mName = strdup(name);
    mDir = strdup(dir);
    
    reset();
}

void Mesh::lost(){
    for(int i=0;i<mNumSubMeshes;i++)
        delete mSubMeshes[i];
}    

Mesh::~Mesh(){
    lost();
    free((void *)mName);
    free((void *)mDir);
}

static Tokeniser gTok; // tokeniser
static MatrixStack gStack;// frame stack. Top of this is current transform
static Mesh *gCurMesh;

#define T_XOF	0
#define T_TEMPLATE	1
#define T_FRAME 2
#define T_FRAMEXFORM 3
#define T_MESH 4
#define T_MESHNORMALS 5
#define T_MESHTEXTURECOORDS 6
#define T_VERTEXDUPLICATIONINDICES 7
#define T_MESHMATERIALLIST 8
#define T_MATERIAL 9
#define T_MESHVERTEXCOLORS 10
#define T_TEXTUREFILENAME 14
#define T_OPCURLY 17
#define T_CLCURLY 18
#define T_END 19
#define T_STRING 20
#define T_IDENT 21
#define T_INT 22
#define T_XVER	23
#define T_FLOAT 24

#define T_SEMI 16
#define T_COMMA 64

static TokenRegistry tokens[]=
{
    {"xof",		T_XOF},
    {"0303txt",  T_XVER},
    {"template",	T_TEMPLATE},
    {"Frame",	T_FRAME},
    {"FrameTransformMatrix",	T_FRAMEXFORM},
    {"Mesh",T_MESH},
    {"MeshNormals",T_MESHNORMALS},
    {"MeshTextureCoords",T_MESHTEXTURECOORDS},
    {"VertexDuplicationIndices",T_VERTEXDUPLICATIONINDICES},
    {"MeshMaterialList",T_MESHMATERIALLIST},
    {"Material",T_MATERIAL},
    {"TextureFilename",T_TEXTUREFILENAME},
    {"MeshVertexColors",T_MESHVERTEXCOLORS},
    
    
    {"*c,",		T_COMMA},
    {"*c;",		T_SEMI},
    {"*c{",		T_OPCURLY},
    {"*c}",		T_CLCURLY},
    
    {"*e",		T_END},
    {"*s",		T_STRING},
    {"*i",		T_IDENT},
    {"*n",		T_INT},
    {"*f",		T_FLOAT},
    
    {NULL,		-10}
};



void Mesh::doparsefailed(int e)
{
    char buf[256];
    const char *b = gTok.getbuf()+gTok.getpos();
    strncpy(buf,b,64);
    printf("position:\n%s\n",buf);
    
    
    sprintf(buf,"%s: mesh parse error E%d at line %d",mName,e,gTok.getline());
    
    throw Exception(buf);
}

void doenforce(int line,int token)
{
    if(gTok.getnext()!=token)
        gCurMesh->doparsefailed(line);
}




#define parsefailed()  doparsefailed(__LINE__)
#define enforce(tok)  doenforce(__LINE__,tok)

void Mesh::reset()
{
    char wd[PATH_MAX];
    
    printf("Reading directory %s  : %s\n",mDir,mName);
    getcwd(wd,PATH_MAX);
    
    if(chdir(mDir))
        throw Exception().set("cannot change to directory '%s'",mDir);
    
    gStack.reset();
    mNumSubMeshes=0;
    gCurMesh=this;
    
    
    QFile file(mName);
    if(!file.open(QIODevice::ReadOnly))
        throw Exception().set("cannot open file %s",mName);
    QByteArray b = file.readAll();
    if(b.isEmpty() || b.isNull())
        throw Exception().set("cannot read file %s",mName);
    b.append((char)0);
    char *buffer = b.data();
    file.close();
    
    gTok.init();
    gTok.settokens(tokens);
    gTok.reset(buffer,buffer+b.size());
    gTok.setcommentlinesequence("//");
    
    // and parse!
    
    enforce(T_XOF);
    enforce(T_XVER);
    
    int n = (int)gTok.getnextfloat();
    if(gTok.iserror())
        parsefailed();
    if(n!=32)
        parsefailed();
    
    while(gTok.getnext()==T_TEMPLATE)
    {
        gTok.getnext(); // skip word
        enforce(T_OPCURLY);
        gTok.skipahead('}');
    }
    
    if(gTok.getcurrent()!=T_FRAME)
        parsefailed();
    
    // Now start parsing frames.
    
    parseFrame();
    chdir(wd);
}

float doparsevalandsep(int line)
{
    float x = gTok.getnextfloat();
    if(gTok.iserror())
        gCurMesh->doparsefailed(line); 
    
    int t = gTok.getnext();
    if(t!=T_COMMA && t!=T_SEMI) 
        gCurMesh->doparsefailed(line);
    return x;
}

#define parsevalandsep() doparsevalandsep(__LINE__)

void Mesh::parseFrame()
{
    // Parsing point : Frame [here] (FrameName) {...
    
    int tok = gTok.getnext();
    if(tok == T_IDENT)
        enforce(T_OPCURLY);
    else if(tok!=T_OPCURLY)
        parsefailed();
    
    for(;;)
    {
        switch(gTok.getnext())
        {
        case T_FRAME:
            gStack.push();
            parseFrame();
            gStack.pop();
            break;
        case T_FRAMEXFORM:
            enforce(T_OPCURLY);
            
            // 16 numbers and two semicolons.
            // Read that matrix and then multiply the current
            // matrix by it.
            {
                Matrix mat;
                for(int i=0;i<16;i++)
                {
                    mat.mf[i] = parsevalandsep();
                }
                enforce(T_SEMI);
                enforce(T_CLCURLY);
                gStack.mul(&mat);
            }
            break;
        case T_MESH:
            {
                if(mNumSubMeshes==16)
                    throw Exception().set("out of submeshes in mesh '%s'!",mName);
                SingleMesh *mesh = new SingleMesh;
                mSubMeshes[mNumSubMeshes++]=mesh;
                mesh->parseMesh();
                mesh->build();
                if(mesh->hastex)hastex=true;
                if(mesh->hasuntex)hasuntex=true;
                
            }
            break;
        case T_CLCURLY:
            return;
        }
    }
}

static Texture *gettexture(const char *name)
{
    if(name && name[0])
    {
        Texture *t = TextureManager::getInstance()->createOrFind(name);
        return t;
    }
    else
        return NULL;
}


void SingleMesh::parseMaterial(MeshMaterial *mat)
{
    mat->tex=NULL;
    
    // we've read the word 'material.' There might be an open curly, or an ID and an open curly, apparently.
    int tok = gTok.getnext();
    if(tok == T_IDENT || tok == T_MATERIAL) // sometimes the ident is "Material" For fuck's sake.
        enforce(T_OPCURLY);
    else if(tok!=T_OPCURLY)
        gCurMesh->parsefailed();
    
    
    
    mat->diffuse.r = parsevalandsep();
    mat->diffuse.g = parsevalandsep();
    mat->diffuse.b = parsevalandsep();
    mat->diffuse.a = parsevalandsep();enforce(T_SEMI);
    
    parsevalandsep(); // power
    
    //specular
    parsevalandsep();parsevalandsep();parsevalandsep();
    enforce(T_SEMI);
    //emissive
    parsevalandsep();parsevalandsep();parsevalandsep();
    enforce(T_SEMI);
    
    // now there might be a texture filename
    
    tok = gTok.getnext();
    
    if(tok == T_TEXTUREFILENAME)
    {
        enforce(T_OPCURLY);
        enforce(T_STRING);
        const char *texname = gTok.getstring();
        mat->tex = gettexture(texname);
        hastex = true;
        
        enforce(T_SEMI);
        enforce(T_CLCURLY);enforce(T_CLCURLY);
    }
    else
    {
        if(tok!=T_CLCURLY)
            gCurMesh->parsefailed();
        hasuntex=true;
    }
}

void SingleMesh::parseMaterialList()
{
    nummats = (int)parsevalandsep();
    if(nummats)
        mats = new MeshMaterial[nummats];
    else
        mats=NULL; // this is valid, weirdly.
    
    int nf = parsevalandsep();
    if(nf!=numfaces){
        printf("Value read: %d, faces parsed: %d\n",nf,numfaces);
    }
    
    matidxs = new int[numfaces];
    // we need to set all the faces, but sometimes fewer than
    // that are provided. In the case of faces which are not
    // provided, set the material index to the last provided face.
    for(int i=0;i<numfaces;i++)
    {
        if(i<nf)
            matidxs[i] = (int)parsevalandsep();
        else
            matidxs[i] = matidxs[nf-1];
    }
    
    int matnum=0;
    for(;;)
    {
        int tok = gTok.getnext();
        switch(tok)
        {
        case T_SEMI:
            break;
        case T_MATERIAL:
            parseMaterial(mats+(matnum++));
            break;
        case T_CLCURLY:
            return;
        default:
            gCurMesh->parsefailed();
        }
    }
}

void SingleMesh::parseMeshNormals()
{
    int i;
    
    numnorms = (int)parsevalandsep(); // get number of normals
    norms = new triple[numnorms];
    
    Matrix xform = *gStack.top();
    xform.setTranslation(0,0,0);
    
    for(i=0;i<numnorms;i++)
    {
        Vector v;
        v.x = parsevalandsep();
        v.y = parsevalandsep();
        v.z = parsevalandsep();
        v.w = 1;
        
        v.transformInPlace(xform);
        
        norms[i].x = v.x;
        norms[i].y = v.y;
        norms[i].z = v.z;
        
        norms[i].normalise();
        
        int tok = gTok.getnext();
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed(); 
    }
    if(i!=numnorms-1)
        gCurMesh->parsefailed();
    
    // face count
    if((int)parsevalandsep() != numfaces)
        gCurMesh->parsefailed(); // must agree with mesh face count
    
    normidxs = new int[outputindicesperface*numfaces];
    int outidx = 0;
    for(i=0;i<numfaces;i++)
    {
        int ipf = parsevalandsep();
//        if(ipf!=indsperface)
//            gCurMesh->parsefailed(); // indsperface must agree with previous value
        
        if(ipf==3)
        {
            for(int j=0;j<3;j++)
            {
                int idx = (int)parsevalandsep();
                normidxs[outidx++]=idx;
            }
        }
        else
        {
            // read the indices and convert the quads into triangles
            int i1 = (int)parsevalandsep();
            int i2 = (int)parsevalandsep();
            int i3 = (int)parsevalandsep();
            int i4 = (int)parsevalandsep();
            
            normidxs[outidx++] = i1;
            normidxs[outidx++] = i2;
            normidxs[outidx++] = i3;
            normidxs[outidx++] = i3;
            normidxs[outidx++] = i4;
            normidxs[outidx++] = i1;
        }
        
        
        int tok = gTok.getnext();
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed();
    }
    if(i!=numfaces-1)
        gCurMesh->parsefailed();
    
    enforce(T_CLCURLY);
    
}
void SingleMesh::parseMeshVertexColors()
{
    // we just skip these
    int n = (int)parsevalandsep();
    int i;
    for(i=0;i<n;i++)
    {
        // get vertex index
        
        enforce(T_INT); // vertex index
        enforce(T_SEMI);
        
        // rgba
        enforce(T_FLOAT);
        enforce(T_SEMI);
        enforce(T_FLOAT);
        enforce(T_SEMI);
        enforce(T_FLOAT);
        enforce(T_SEMI);
        enforce(T_FLOAT);
        enforce(T_SEMI);
        
        int tok = gTok.getnext();
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed();
    }
    if(i!=n-1)
        gCurMesh->parsefailed(); // premature end
    enforce(T_CLCURLY);
}
void SingleMesh::parseMeshTextureCoords()
{
    int n = (int)parsevalandsep();
    if(n!=numverts)
        gCurMesh->parsefailed();
    
    uvs = new uv[n];
    
    int i;
    for(i=0;i<n;i++)
    {
        uvs[i].u = parsevalandsep();
        uvs[i].v = 1.0f-parsevalandsep();
        int tok = gTok.getnext();
        
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed();
    }
    if(i!=n-1)
        gCurMesh->parsefailed();
    enforce(T_CLCURLY);
}
void SingleMesh::parseVertDups()
{
    // easy - we just throw them away
    enforce(T_INT);
    enforce(T_SEMI);
    enforce(T_INT);
    enforce(T_SEMI);
    
    for(;;)
    {
        enforce(T_INT);
        int tok = gTok.getnext();
        if(tok == T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed();
    }
    enforce(T_CLCURLY);
}

void SingleMesh::parseMesh()
{
    // parse point: Mesh [here] { ...
    
    uvs = NULL;
    verts = NULL;
    norms = NULL;
    
    if(gTok.getnext()!=T_OPCURLY)
        gCurMesh->parsefailed(); 
    
    // How many verts there are
    
    numverts = (int)gTok.getnextfloat();
    if(gTok.iserror())
        gCurMesh->parsefailed(); 
    
    enforce(T_SEMI);
    
    verts = new triple[numverts];
    
    Matrix *xform = gStack.top();
    
    
    // and read that many triples - the geometric coordinate data
    int i;
    for(i=0;i<numverts;i++)
    {
        Vector v;
        v.x = parsevalandsep();
        v.y = parsevalandsep();
        v.z = parsevalandsep();
        v.w = 1;
        
        v.transformInPlace(*xform);
        
        verts[i].x = v.x;
        verts[i].y = v.y;
        verts[i].z = v.z;
        
        int tok = gTok.getnext();
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed(); 
    }
    if(i!=numverts-1)
        gCurMesh->parsefailed(); // too few verts!
    
    // now read the number of faces, and construct the face index array
    
    numfaces = (int)parsevalandsep();
    indsperface = -1;
    
    int outidx=0;
    // now we construct the index buffer for x,y,z face data
    
    for(i=0;i<numfaces;i++)
    {
        int tmp = (int)parsevalandsep();
        
        if(indsperface<0){
            if(tmp!=3 && tmp!=4)
                gCurMesh->parsefailed(); // can only support triangles and quads!
            indsperface=tmp;
            outputindicesperface = (indsperface==4) ? 6: 3;// will need 6 indices for each quad
            vertidxs = new int[outputindicesperface*numfaces]; 
        }
        else if(tmp!=indsperface)
            throw Exception("indices per face changed in mesh");
        
        if(tmp == 3)
        {
            for(int j=0;j<3;j++)
            {
                int idx = (int)parsevalandsep();
                vertidxs[outidx++]=idx;
            }
        }
        else if(tmp==4)
        {
            // read the indices and convert the quads into triangles
            int i1 = (int)parsevalandsep();
            int i2 = (int)parsevalandsep();
            int i3 = (int)parsevalandsep();
            int i4 = (int)parsevalandsep();
            
            vertidxs[outidx++] = i1;
            vertidxs[outidx++] = i2;
            vertidxs[outidx++] = i3;
            vertidxs[outidx++] = i3;
            vertidxs[outidx++] = i4;
            vertidxs[outidx++] = i1;
        } else
            throw Exception("neither triangle nor quad");
        
        int tok = gTok.getnext();
        if(tok==T_SEMI)break;
        else if(tok!=T_COMMA)
            gCurMesh->parsefailed();
        
        
    }
    if(i!=numfaces-1)
        gCurMesh->parsefailed();
    
    // now bring in the other stuff
    
    for(;;)
    {
        int tok = gTok.getnext();
        if(tok==T_CLCURLY)break;
        
        enforce(T_OPCURLY); // they all start with this.
        
        switch(tok)
        {
        case T_MESHMATERIALLIST:
            parseMaterialList();break;
        case T_MESHNORMALS:
            parseMeshNormals();break;
        case T_MESHVERTEXCOLORS:
            parseMeshVertexColors();break;
        case T_MESHTEXTURECOORDS:
            parseMeshTextureCoords();break;
        case T_VERTEXDUPLICATIONINDICES:
            parseVertDups();break;
        }
    }
    
    // this is the end of the mesh parsing, we need to actually build the mesh data in GL form.
}

void SingleMesh::build()
{
    // this will tidy up the structures, collate all the data, and build openGL buffers.
    
    int i;
    
    // first, deal with materialless meshes.
    if(nummats==0)
    {
        mats = new MeshMaterial[1]; // have to create as an array
        mats->setDefault();
        nummats=1;
        this->hasuntex = true; // must be untextured, this default material
    }
    
    // and now begin to construct an index and vertex buffer.
    
    // create our index buffer
    indices = (unsigned short *)memalign(16,outputindicesperface*numfaces*sizeof(unsigned short));
    int indsout=0;
    
    // create a new lit vertex buffer, with enough room for the worst case
    UNLITVERTEX *tmpv = new UNLITVERTEX[outputindicesperface*numfaces];
    vertexcount = 0;
    
    for(i=0;i<numfaces*outputindicesperface;i++)
    {
        // get the assorted data and build a vertex
        UNLITVERTEX v;
        triple *thisv = verts+vertidxs[i];
        v.x = thisv->x;
        v.y = thisv->y;
        v.z = thisv->z;
        triple *thisn = norms+normidxs[i];
#if 1
        v.nx = thisn->x;
        v.ny = thisn->y;
        v.nz = thisn->z;
#else
        // HACK NORMALS
        Vector q,hack(v.x,v.y,v.z);q.normalize(hack);
        v.nx = q.x;
        v.ny = q.y;
        v.nz = q.z;
#endif
        
        if(uvs)
        {
            uv *thisuv = uvs+vertidxs[i];
            v.u = thisuv->u;
            v.v = thisuv->v;
        }
        else
        {
            v.u = v.v = 0;
        }
        
        // look for this vertex in our output buffer. If it's there already, use it.
        
        int found=-1;;
        for(int j=0;j<vertexcount;j++)
        {
            if(v.compare(tmpv+j))
            {
                found=j; break;
            }
        }
        if(found<0)
        {
            // otherwise copy it
            tmpv[vertexcount]=v;
            found=vertexcount++;
        }
        // and add that vertex to the index buffer
        if(found>65535)
            gCurMesh->parsefailed();
        indices[indsout++] = (unsigned short)found;
    }
    
    // we now have the index buffer, and the vertex buffer can be copied over.
    
    vertices = (UNLITVERTEX*)memalign(32,sizeof(UNLITVERTEX)*vertexcount);
    memcpy(vertices,&(tmpv[0]),sizeof(UNLITVERTEX)*vertexcount);
    
    delete [] tmpv; // delete the larger temporary buffer.
    
    
    // Now we've done that, let's do the material transitions.
    
    // First count them.
    
    int curmat = -1;
    matblockcount=0;
    for(i=0;i<numfaces;i++)
    {
        if(matidxs[i]!=curmat)
        {
            curmat=matidxs[i];
            matblockcount++;
        }
    }
    
    // that being done, we can now actually create them.
    
    matblocks = new MeshMaterialBlock[matblockcount];
    
    curmat = -1;
    matblockcount=0;
    for(i=0;i<numfaces;i++)
    {
        if(matidxs[i]!=curmat)
        {
            curmat=matidxs[i];
            matblocks[matblockcount].matidx = curmat;
            matblocks[matblockcount].start = i*outputindicesperface;
            if(matblockcount)
                matblocks[matblockcount-1].count = i*outputindicesperface-matblocks[matblockcount-1].start;
            matblockcount++;
        }
    }
    matblocks[matblockcount-1].count = i*outputindicesperface-matblocks[matblockcount-1].start;
    
    // now actually create the openGL buffers
    
    // create index and vertex buffers
    glGenBuffers(2,buffers);
    ERRCHK;
    
    // bind the array and element array buffer to our buffers
    glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEXBUFFER]);
    ERRCHK;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[INDEXBUFFER]);
    ERRCHK;
    
    // create the vertex and index buffer and fill them with data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*numfaces*outputindicesperface,indices,GL_STATIC_DRAW);
    ERRCHK;
    glBufferData(GL_ARRAY_BUFFER,sizeof(UNLITVERTEX)*vertexcount,vertices,GL_STATIC_DRAW);
    ERRCHK;
    
    // unbind, we're done.
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    
    cleanUp();
}



/*****************************************************************************
 * 
 * main renderer
 * 
 ****************************************************************************/

void Mesh::render(Matrix *view,Matrix *world){
    if(hastex)renderTex(view,world);
    if(hasuntex)renderUntex(view,world);
    
    // stop VBO rendering
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}



/*****************************************************************************
 * 
 * textured rendering
 * 
 ****************************************************************************/


void Mesh::renderTex(Matrix *view,Matrix *world)
{
    // start the effect
    MeshTexEffect *eff = mTexEffect?mTexEffect:
    EffectManager::getInstance()->meshTex;
    
//    printf("Using eff %s\n",eff->getFileName());
    eff->begin(view);
    // upload the matrices
    eff->setWorldMatrix(world);
    
    // iterate over the submeshes, only those which have textures.
    
    for(int i=0;i<mNumSubMeshes;i++)
        if(mSubMeshes[i]->hastex)
            mSubMeshes[i]->renderTex(eff);
    eff->end();
}

void SingleMesh::renderTex(MeshTexEffect *eff)
{
    // bind the arrays
    glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEXBUFFER]);
    ERRCHK;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[INDEXBUFFER]);
    ERRCHK;
    
//    printf("Using eff %s\n",eff->getFileName());
    // and tell them bout the offsets
    eff->setArrays();
    
    for(int i=0;i<matblockcount;i++)
    {
        // draw only textured mats
        MeshMaterialBlock *b = matblocks+i;
        MeshMaterial *m = mats+b->matidx;
        if(m->tex)
        {
            eff->setMaterial((float*)&m->diffuse,m->tex);
            glDrawElements(GL_TRIANGLES,b->count,GL_UNSIGNED_SHORT,(void *)(b->start*sizeof(unsigned short)));
            ERRCHK;
        }
    }
}

/*****************************************************************************
 * 
 * untextured rendering
 * 
 ****************************************************************************/

void Mesh::renderUntex(Matrix *view,Matrix *world)
{
        // start the effect
    MeshUntexEffect *eff = mUntexEffect?mUntexEffect:
    EffectManager::getInstance()->meshUntex;
    
//    printf("Using eff %s\n",eff->getFileName());
    eff->begin(view);
    // upload the matrices
    eff->setWorldMatrix(world);
    
    // iterate over the submeshes, only those which have untex set.
    
    for(int i=0;i<mNumSubMeshes;i++)
        if(mSubMeshes[i]->hasuntex)
            mSubMeshes[i]->renderUntex(eff);
    eff->end();
}

void SingleMesh::renderUntex(MeshUntexEffect *eff)
{
    // bind the arrays
    glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEXBUFFER]);
    ERRCHK;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[INDEXBUFFER]);
    ERRCHK;
    
//    printf("Using eff %s\n",eff->getFileName());
    // and tell them bout the offsets
    eff->setArrays();
    
    
    for(int i=0;i<matblockcount;i++)
    {
        MeshMaterialBlock *b = matblocks+i;
        MeshMaterial *m = mats+b->matidx;
        // draw only untextured mats
        if(!m->tex)
        {
            eff->setMaterial((float*)&m->diffuse);
            glDrawElements(GL_TRIANGLES,b->count,GL_UNSIGNED_SHORT,(void *)(b->start*sizeof(unsigned short)));
            ERRCHK;
        }
    }
}

