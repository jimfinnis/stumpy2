/**
 * \file The definitions of the classes which represent running instances
 * of patches and components.
 *
 * 
 * \author jaf18
 */

#ifndef __INSTANCES_H
#define __INSTANCES_H

#include "util/time.h"

class ComponentInstance;

/// an instance of a patch

class PatchInstance {
public:
    ListNode<PatchInstance> listnodes[1]; //!< make me able to be in a list
    Patch *patch; //!< the patch of which I am an instance
    bool valid;
    
    /// this just allocates the component instance pool;
    /// we still need to initialise the data therein. This
    /// is done by the instantiating patch.
    PatchInstance(class Patch *p);
    
    /// return a component instance given the slot number
    ComponentInstance *getInstance(int slot);
   
    /// return a component instance given the component
    ComponentInstance *getInstance(Component *c);
    
    
    ComponentInstance *instances;
    
    //TODO destroying the instance we're currently using as the primary should cause problems,
    //TODO as should deleting an instance which is currently used by a macro!
    ~PatchInstance();
    
    /// run the instance
    void run();
        
};


/// an instance of a component - uses init() and shutdown() rather than 
/// ctor and dtor. This contains information used by each instance of
/// the component in a running patch instance: the output values,
/// the private data etc.

struct ComponentInstance {
    Component *component; //!< the component of which I am an instance, or NULL if unused
    PatchInstance *patchInst;
    Patch *patch;
    void *privateData; //!< this is a pointer which initComponentInstance and shutdownComponentInstance must deal with if they are implemented.
    
    /// constructor sets up default uninitialised state
    ComponentInstance(){
        component = NULL;
    }
    
    /// a null data for unconnected inputs
    static ConnectionValue noData;
    
    /// the last tick this instance updated the given output
    uint32_t updatedOutputTime[ComponentType::NUMOUTPUTS]; 
          
    /// the value of my outputs, which run() will write
    ConnectionValue outputs[ComponentType::NUMOUTPUTS];
    
    /// shutdown the instance, which will call the type's
    /// instance shutdown code.
    
    ~ComponentInstance(){
        if(isUsed()) // if initialised..
            shutdown();
    }
    
    bool isUsed(){
        return component!=NULL;
    }
    
    /// initialise this instance, associating it with a component and 
    /// calling the init instance code. Will also clear the inputs and outputs.
    
    void init(Component *c,PatchInstance *pi){
        patchInst = pi;
        patch = pi->patch;
        
        printf("initialising c-instance %p\n",this);
        
        if(!c->type)
            throw Exception("component instance init for uninited component");
        component=c;
        c->type->initComponentInstance(this);
        
        // initialise inputs and outputs
        
        for(int i=0;i<ComponentType::NUMOUTPUTS;i++){
            updatedOutputTime[i]=-1;
            outputs[i] = noData;
        }
    }
    
    /// quick way of determining input connection status
    inline bool isInputConnected(int n){
        return component->isInputConnected(n);
    }
    
    /// get the value of an input. No range checking, for speed!
    /// This will cause getOutput to run on the connected component.
    inline ConnectionValue &getInput(int n){
        if(component->isInputConnected(n)){
            // it's connected. Get the connected component and output number.
            const Component::Input *outputData = component->getInput(n);
            // get the instance for that component
            ComponentInstance *outputInst = patchInst->getInstance(outputData->c);
            // and request the output from it
#if TRACE
            printf("  %p : input %d -> %p/%d\n",this,n,outputInst,outputData->output);
#endif
            return outputInst->getOutput(outputData->output);
        } else {
#if TRACE
            printf("  %p : input %d -> not connected\n",this,n);
#endif
            return noData;
        }
    }
    
    /// get the value of an output. If the component has not run this tick for that output,
    /// and is not set to "run always", will just return the output. Otherwise
    /// will run the component for that output
    inline ConnectionValue &getOutput(int n){
        if(component->runAlways[n] || isFirstCallThisFrameForOutput(n)){
            component->type->run(this,n);
        }
        return outputs[n];
    }
    
    /// true if this is the first time that the component has been run on this frame, for
    /// this output
    inline bool isFirstCallThisFrameForOutput(int n){
        if(updatedOutputTime[n]!=Time::ticks()){
            return true;
        } else
            return false;
    }
    
    /// get the output FOR SETTING. No range checking, for speed! If this isn't called
    /// for a component, the isFirstCallThisFrameForOutput() call will always return true.
    /// Returns a reference to a value which can be set.
    inline ConnectionValue& output(int n){
        updatedOutputTime[n]=Time::ticks();
        return outputs[n];
    }
    
    void shutdown(){
        if(component){
            printf("shutting down c-instance %p\n",this);
            component->type->shutdownComponentInstance(this);
            component=NULL;
        }
    }
};




#endif /* __INSTANCES_H */
