/**
 * \file The component and component type classes. Each component within
 * a patch is represented by a Component object. These are all of the same
 * class - the differences in behaviour are represented by which ComponentType
 * object they are linked to. These latter objects are singletons which self-register
 * by adding themselves into the type list on construction.
 *
 * 
 * \author jaf18
 */


#ifndef __COMPONENT_H
#define __COMPONENT_H

#define UNUSED __attribute__((unused))

#include "util/exception.h"
#include "list.h"
#include "intkeyedhash.h"
#include "errors.h"
#include "param.h"

class Component;
class ComponentInstance;


/// the various connection types

enum ConnectionType {
    T_FLOW, //!< a flow
          T_FLOAT, //!< a numeric value
          T_INVALID, //!< not yet defined
};

/// a union incorporating the different values for connections;
/// one entry for each ConnectionType

union ConnectionValue {
    float f;
    int i;
    
    ConnectionValue(){
        i=0;
    }
    
    static ConnectionValue makeFloat(float f){
        ConnectionValue t;
        t.f = f;
        return t;
    }
    static ConnectionValue makeInt(float i){
        ConnectionValue t;
        t.i = i;
        return t;
    }
    
};



/// a component type object, defining what a component can do.
/// There's one of these for each type of component. They are
/// self-registered by defining a single static instance,
/// e.g. "static TestComponent reg;" in their source file.
/// The ComponentType constructor will create the type list
/// if it doesn't exist and add the new object to it.

class ComponentType {
public:
    static const int NUMINPUTS = 16;
    static const int NUMOUTPUTS = 16;
    
    /// this boolean is only set for components with no
    /// outputs which are run directly by PatchInstance::run()
    /// such as the "output" component.
    
    bool isRoot;
    
    /// if this is set for a given output, the component will run for that 
    /// output whether it has already done so for this tick or not.
    bool runAlways[NUMOUTPUTS];
    
    const char *name;
    
    /// make me able to be in one list
    ListNode<ComponentType> listnodes[1];
    
    /// static list of type objects, starts out as null and
    /// initialised by the ComponentType constructor if null.
    /// The constructor adds the newly created object to this list.
    static LinkedList<ComponentType,0> *types;
    
    /// create new type. Naturally you'll override this. This will add the
    /// type to the internal static type list (initialising it if
    /// necessary)
    
    ComponentType(const char *n){
        isRoot=false;
        name = strdup(n);
        for(int i=0;i<NUMINPUTS;i++)inputTypes[i]=T_INVALID;
        for(int i=0;i<NUMOUTPUTS;i++){outputTypes[i]=T_INVALID;
            runAlways[i]=false;
        }
        
        if(!types)
            types = new LinkedList<ComponentType,0>();
        types->addToTail(this);
        
        printf("Component registered: %s\n",n);
    }
    
    /// get a pointer to a given type.
    static ComponentType *getType(const char *n){
        for(ComponentType *t = types->head();t;t=types->next(t)){
            if(!strcmp(t->name,n))return t;
        }
        throw(SE_NOSUCHCOMPT);
    }
    
    /// run the component, in order to get the numbered output.
    /// For a root component, running this once will run the entire
    /// component.
    virtual void run(ComponentInstance *ci, int output) = 0;
    
    /// initialise a component of this type, as it appears in the patch, not each instance.
    /// Creates the parameter array and sets up the parameters.
    virtual void initComponent(Component *c)=0;
    
    /// shutdown a component of this type
    virtual void shutdownComponent(UNUSED Component *c){}
    
    /// initialise the private runtime data
    virtual void initComponentInstance(UNUSED ComponentInstance *c){};
    
    /// shutdown the private runtime data
    virtual void shutdownComponentInstance(UNUSED ComponentInstance *c){};
    
    /// an array of the types (T_FLOAT, T_FLOW etc.) of each output
    
    ConnectionType inputTypes[NUMINPUTS];
    ConnectionType outputTypes[NUMOUTPUTS];
    
    /// get the type of a given input, checking for validity
    
    inline ConnectionType getInputType(int n){
        assertInputInRange(n);
        return inputTypes[n];
    }
    
    /// get the type of a given output, checking for validity
    
    inline ConnectionType getOutputType(int n){
        assertOutputInRange(n);
        return outputTypes[n];
    }
        
private:
    
    void assertInputInRange(int n){
        if(n<0||n>=NUMINPUTS)
            throw SE_INPUTRANGE;
    }
    void assertOutputInRange(int n){
        if(n<0||n>=NUMOUTPUTS)
            throw SE_OUTPUTRANGE;
    }
protected:
    /// use this in the ctor to set up the connections
    void setInput(int n, ConnectionType t){
        assertInputInRange(n);
        inputTypes[n]=t;
    }
    /// use this in the ctor to set up the connections
    void setOutput(int n, ConnectionType t){
        assertOutputInRange(n);
        outputTypes[n]=t;
    }
    /// make the component always run when a value for this output
    /// is requested, even if this is done multiple times in the same tick.
    void setOutputRunAlways(int n){
        runAlways[n] = true;
    }
    
};



/// a component, which does not contain runtime data - that
/// goes in the component instance data.

class Component {
public:
    /// data about a an input - which component and which output it is connected to
    struct Input {
        Component *c;
        int output;
    };
    
private:    
    
    inline void assertInputInRange(int i){
        if(i<0||i>=ComponentType::NUMINPUTS)
            throw SE_INPUTRANGE;
    }
    
    /// a component connection - this tells which output an input is wired to.

    Input inputs[ComponentType::NUMINPUTS];
    
protected:
    /// the number of pointers in the params array, also set
    /// up by the type's init method.
    int paramct;
    
public:
    
    /// a pointer to an array of parameter pointers,
    /// set up by the component type's init method calling setParams().
    /// This is used by the parameter's get() function, when the component type's
    /// parameter pointer (actually a pointer to the last created component's
    /// parameter) uses this table to get the component's own parameters.
    Parameter **params;
    
    /// set the array of parameters. Terminate will NULL.
    /// Allocate each with new. This should be called from the
    /// component type's init method.
    void setParams(Parameter *p,...);
    
    /// set a parameter's value from an encoded value and type code.
    void setParamValue(int paramnum,char code,const char *val){
        if(paramnum>=paramct)
            throw SE_NOSUCHPARAM;
        params[paramnum]->setValue(code,val);
    }
    
    /// the containing class
    class Patch *patch;
    
    /// return data about an input. No range check, for speed.
    const Input *getInput(int i){
        return inputs+i;
    }
    
    /// link an input
    void linkInput(int i,Component *c,int output){
        assertInputInRange(i);
        if(!type)
            throw SE_LINKUNINIT;
        if(!c->type)
            throw SE_LINKUNINIT;
        
        if(type->getInputType(i) != c->type->getOutputType(output)){
            printf("Input component : %s, input number : %d\n",
                   type->name,i);
            printf("Output component : %s, output number : %d\n",
                   c->type->name,output);
            throw SE_LINKMISMATCH;
        }
        inputs[i].c = c;
        inputs[i].output = output;
    }
    
    
    /// unlink an input - unlink output has to be done by the patch, so see there.
    void unlinkInput(int i){
        assertInputInRange(i);
        inputs[i].c = NULL;
    }
    
    /// check an input is connected. No range check for speed.
    inline bool isInputConnected(int i){
        return inputs[i].c != NULL;
    }
    
    
        
    
    /// unlink any inputs which come from the given component (which is being removed)
    void unlinkInputsFrom(Component *c){
        for(int i=0;i<ComponentType::NUMINPUTS;i++){
            if(inputs[i].c==c)
                unlinkInput(i);
        }
    }
    
    /// construct the component - the private data slot and type
    /// are set to uninitialised, and the inputs are all unconnected.
    Component(){
        slot = -1;
        type = NULL;
        for(int i=0;i<ComponentType::NUMINPUTS;i++){
            inputs[i].c=NULL;
        }
    }
    
        
    
    /// the patch will deallocate the component slot and detach any inputs feeding from me
    ~Component(){
        printf("shutting down component %p",this);
        if(type){
            // call shutdown in the type
            type->shutdownComponent(this);
            // delete any parameters
            if(paramct){
                for(int i=0;i<paramct;i++){
                    printf("deleting param %d\n",i);
                    delete params[i];
                }
                printf("deleting param array\n");
                delete[] params;
            }
            type = NULL;
        }
    }
    
    /// run the type's initialisation code, which has to be done after the ctor, because
    /// at that point we don't know what the type is.
    void init(){
        if(!type)
            throw Exception("cannot init component with no type");
        type->initComponent(this);
    }
    
    
    
    
    /// the slot number - i.e. the index of the private runtime data in the patch instance.
    
    int slot;
    void setSlot(int s){
        if(slot!=-1)
            throw Exception("slot type already assigned");
        slot = s;
    }
    
    ComponentType *type; //!< the component type
    
    /// set up the component according to it's type; completes
    /// the initialisation
    
    void setType(ComponentType *t){
        if(type != NULL)
            throw Exception("component type already assigned");
        type = t;
    }
};



#endif /* __COMPONENT_H */
