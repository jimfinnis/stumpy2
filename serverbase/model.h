/**
 * @file
 * This file contains details of the model used by the system,
 * mainly by including other files.
 *
 * 
 * 
 */

#ifndef __MODEL_H
#define __MODEL_H

#include <stdint.h>
#include "patch.h"



/// A patch library, which is a bunch of patches

class PatchLibrary {
    /// integer-keyed hash of patches
    IntKeyedHash<Patch> patches;
    
public:
    
    PatchLibrary(){
        printf("constructing patch library at %p\n",this);
        active = NULL;
    }
    
    /// create a new patch in the library
    Patch *create(uint32_t id){
        Patch *p = patches.set(id);  // will run a constructor
        p->library = this;
        return p;
    }
    
    /// get the patch associated with a given ID, or NULL
    Patch *get(uint32_t id){
        if(patches.find(id))
            return patches.getval();
        else
            return NULL;
    }
    
    /// delete a patch - and deconstruct it, and its instances.
    bool del(uint32_t id){
        return patches.del(id);
    }
    
    /// delete and deconstruct all patches and instances
    void clear(){
        patches.clear();
    }
    
    /// the currently running patch instance if any
    PatchInstance *active;
        
    /// attempt to instantiate this patch. If a patch is running
    /// running, destroy the previous instance.
    void instantiateAsActive(uint32_t id);
    
    /// run any active patch within this library - the actual
    /// "do something" method!
    
    void run(){
        if(active)
            active->run();
    }
    
    /// read a load of server commands from a file using a controller
    /// with a dummy Responder instead of a real server.
    void readFile(const char *fn);
        
};



#endif /* __MODEL_H */
