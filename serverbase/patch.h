/**
 * @file This file contains details of the patches, built
 * out of the components described in component.h
 *
 * 
 * 
 */
#ifndef __PATCH_H
#define __PATCH_H

#include "component.h"
#include "stdConns.h"
#include "instances.h"

class PatchInstance;

/// a patch, which consists of components (but not their private runtime data).
/// The private data for each component is kept in a ComponentInstance for each patch instance.
/// The PatchInstances operate as pools of ComponentInstances, but the freelist for these
/// pools is kept in the Patch - so that the index of the data in the pools is always the same.
/// Components then store the indices.

class Patch {
    friend class PatchInstance;
    static const int INITIALPOOLSIZE = 128; 
    static const int NUMCONNECTORS = 128;
    
    int *freeList; //!< the freelist for the component instance data pools
    int freeListSize; //!< the current size of the freelist
    int firstFree; //!< the first free item in the freelist
    bool valid; //!< cleared on deletion, just in case
    
    /// allocate a new component slot. May cause the pool to resize, in which
    /// case all the instances will have to resize.
    
    int allocateNewComponentSlot(){
        if(firstFree<0)
            // TODO  - ADD GROW CODE HERE
            throw Exception("patch component pool out of memory");
        int id = firstFree;
        firstFree = freeList[firstFree];
        return id;
    }
        
    
    /// deallocate a component slot.
    // TODO - should also delete the instance data, but that may not be required.
    void deallocateComponentSlot(int id){
        freeList[id] = firstFree;
        firstFree = id;
    }
    
public:
    /// a list of instances (see LinkedList - we're using listnode 0 to link these)
    LinkedList<class PatchInstance,0> instances;
    
    /// integer-keyed hash of components
    IntKeyedHash<Component> components;
    
    // the connection table for this patch, used by the connectin
    // and connectout indirect connection components
    Component::Input connectors[NUMCONNECTORS];
    
    /// the library we're in, which must be set from the outside
    /// (since we're using hash semantics to construct)
    
    class PatchLibrary *library;
    
    Patch(){
        printf("constructing patch at %p\n",this);
        
        freeList = new int[INITIALPOOLSIZE];
        for(int i=0;i<INITIALPOOLSIZE;i++)
            freeList[i]=i+1;
        firstFree=0;
        library = NULL;
        valid = true;
        for(int i=0;i<NUMCONNECTORS;i++)
            connectors[i].c=NULL;
    }
    
    /// dump all components (type and ID) to stdout
    void dump(){
        IteratorPtr<uint32_t> iterator(components.createKeyIterator());
    
        for(iterator->first();!iterator->isDone();iterator->next()){
            uint32_t key = iterator->current();
            if(components.find(key)){
               printf("%d : %s\n",key,components.getval()->type->name); 
            } else 
                printf("%d : --- ERROR cannot retrieve key, but is in iterator\n",key);
        }
    }
        
        
    
    /// create a new component and assign it a slot and a type.
    Component *createComponent(uint32_t id,const char *type);
    
    /// delete a component and clear all its instance data. Should disconnect, too.
    void deleteComponent(uint32_t id);
    
    /// toggle debugging on a component
    void toggleDebugComponent(uint32_t id);
    
    /// remove an instance from the instances list - is done
    /// by the instance destructor
    
    void removeInstance(class PatchInstance *pi){
        instances.remove(pi);
    }
    
    /// find a component
    Component *getComponent(uint32_t id){
        if(!components.find(id))
            return NULL;
        else
            return components.getval();
    }
    
    /// create a new instance of the patch, adding it to the instances
    /// list
    PatchInstance *instantiate();
    
    /// Unlink a given component's output, unlinking all the inputs connected to it -
    /// this has to be in the patch, because it has to traverse all the components.
    void unlinkComponentOutput(Component *c,int output);
    
    
    
    /// destroy the patch AND its instances, and their component instances.
    ~Patch();
};



#endif /* __PATCH_H */
