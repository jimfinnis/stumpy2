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

// default client screen data
#define DEFAULTWIDTH 70
#define DEFAULTHEIGHT 30

class Component;
class ComponentInstance;

extern LinkedList<class ConnectionType,0> connectionTypeList;


/// Connection types, which need to be registered by the application.
/// Each connection type indicates the name, ID, rendering colour
/// and underlying C++ type.
/// Connection values are a structure of the type pointer and a
/// union of those underlying types.

enum ConnectionBaseType {
    FLOAT, //!< 32-bit float
    INT, //!< 32-bit signed int          
    BITFIELD, //!< 128-bit field
          
    NONE //!< no value (such as the "flow" type)
};

struct ConnectionType {
    const char *name; //!< type name
    uint32_t col; //!< rendering colour (rgba)
    ConnectionBaseType base; //!< the underlying C++ type
    
    /// make me able to be in one list
    ListNode<ConnectionType> listnodes[1];
    
    int id; //!< unique type ID (passed to client)
    /// will create and register the type
    ConnectionType(int id,const char *n,uint32_t c,ConnectionBaseType b);
    
    /// get type by ID
    static ConnectionType *get(int id);
};

/// a simple 128-bitfield
class BitField {
private:
    uint32_t bits[4];
public:
    /// can't have a ctor because it won't go in the union
    /// without complicating matters.
    void clear(){
        for(int i=0;i<4;i++)bits[i]=0;
    }
    bool get(int b) const{
        uint32_t i = bits[b>>5];
        return (i & (1<<(b&0x1f)))!=0;
    }
    void set(int b,bool v){
        uint32_t *i = bits+(b>>5);
        if(v){
            *i |= 1<<(b&0x1f);
        } else {
            *i &= ~(1<<(b&0x1f));
        }
    }
};

/// a struct + union incorporating the different values for connections.

struct ConnectionValue {
    ConnectionType *t;
    ConnectionValue(){
        t=NULL; // indicates no data
    }
    union {
        float f;
        int i;
        BitField b;
    } d;
    
    void setNoData(){
        if(t){
            switch(t->base){
            case FLOAT:d.f=0;break;
            case INT:d.f=0;break;
            case BITFIELD:d.b.clear();break;
            default:break;
            }
        }
    }
};



/// a component type object, defining what a component can do.
/// There's one of these for each type of component. They are
/// self-registered by defining a single static instance,
/// e.g. "static TestComponent reg;" in their source file.
/// The ComponentType constructor will create the type list
/// if it doesn't exist and add the new object to it.

class ComponentType {
    friend class Component;
public:
    static const int NUMINPUTS = 16;
    static const int NUMOUTPUTS = 16;
    static const int MAXPARAMS = 32;
    
    const char *inputNames[ComponentType::NUMINPUTS];
    const char *outputNames[ComponentType::NUMOUTPUTS];
    
    
    /// editor data, not used here but uploaded to the client
    int width,height;
    
    /// this boolean is only set for components with no
    /// outputs which are run directly by PatchInstance::run()
    /// such as the "output" component.
    
    bool isRoot;
    
    const char *name,*category;
    
    /// the parameter list - each component also has a copy
    /// of this list, containing a copy of these.
    Parameter *params[MAXPARAMS];
    /// number of parameters
    int paramct;
    
    /// make me able to be in one list
    ListNode<ComponentType> listnodes[1];
    
    /// static list of type objects, starts out as null and
    /// initialised by the ComponentType constructor if null.
    /// The constructor adds the newly created object to this list.
    static LinkedList<ComponentType,0> *types;
    
    /// create new type. ONLY OVERRIDE THIS WITH AN EMPTY BODY -
    /// use init() instead for other stuff. This will add the
    /// type to the internal static type list (initialising it if
    /// necessary)
    
    ComponentType(const char *n,const char *cat){
        isRoot=false;
        
        name = n;
        category = cat;
        
        width=DEFAULTWIDTH;
        height=DEFAULTHEIGHT;
              
        for(int i=0;i<NUMINPUTS;i++)inputTypes[i]=NULL;
        for(int i=0;i<NUMOUTPUTS;i++)outputTypes[i]=NULL;
        
        if(!types)
            types = new LinkedList<ComponentType,0>();
        types->addToTail(this);
        paramct=0;
        
        printf("Component registered: %s\n",n);
    }
    
    /// this is what you need to override to set up the new type.
    /// It's this way to allow autoregistration by declaring a static,
    /// without the static initialisation order fiasco.
    virtual void init()=0;
    
    /// get a pointer to a given type.
    static ComponentType *getType(const char *n){
        for(ComponentType *t = types->head();t;t=types->next(t)){
            if(!strcmp(t->name,n))return t;
        }
        throw(SE_NOSUCHCOMPT);
    }
    
    /// run through all the components, calling their init()s. Done
    /// after connection types have all been registered, in the server
    /// startup.
    static void initAll(){
        for(ComponentType *t = types->head();t;t=types->next(t)){
            t->init();
        }
    }
        
    
    /// run the component, in order to get the numbered output.
    /// For a root component, running this once will run the entire
    /// component.
    virtual void run(ComponentInstance *ci, int output) = 0;
    
    /// initialise a component of this type, as it appears in the patch, not each instance.
    /// Sometimes it does nothing at all, since parameter and connector
    /// setting is done by the framework. 
    virtual void initComponent(UNUSED Component *c){}
    
    /// shutdown a component of this type
    virtual void shutdownComponent(UNUSED Component *c){}
    
    /// initialise the private runtime data
    virtual void initComponentInstance(UNUSED ComponentInstance *c){};
    
    /// shutdown the private runtime data
    virtual void shutdownComponentInstance(UNUSED ComponentInstance *c){};
    
    /// call after param update and creation, gets an optional string
    /// to display in the editor's box
    virtual const char *getExtraText(UNUSED Component *c,char *buf)
    {return NULL;}
    
    
    /// an array of the types of each output
    
    ConnectionType *inputTypes[NUMINPUTS];
    ConnectionType *outputTypes[NUMOUTPUTS];
    
    /// get the type of a given input, checking for validity
    
    inline ConnectionType *getInputType(int n){
        assertInputInRange(n);
        return inputTypes[n];
    }
    
    /// get the type of a given output, checking for validity
    
    inline ConnectionType *getOutputType(int n){
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
    void setInput(int n, ConnectionType *t,const char *name){
        assertInputInRange(n);
        inputTypes[n]=t;
        inputNames[n]=name;
    }
    /// use this in the ctor to set up the connections
    void setOutput(int n, ConnectionType *t,const char *name){
        assertOutputInRange(n);
        outputTypes[n]=t;
        outputNames[n]=name;
    }
    
    /// add a parameter to this component type - you might also
    /// want to add it as a member of the subclass. Will set the
    /// index field of the parameter.
    void addParameter(Parameter *p){
        if(paramct==MAXPARAMS)
            throw SE_TOOMANYPARAMS;
        p->idx = paramct;
        params[paramct++]=p;
    }
    
    /// set the array of parameters. Terminate will NULL.
    /// Allocate each with new. This should be called from
    /// the constructor of the subclass
    void setParams(Parameter *p,...);
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
    
public:
    
    
    /// pointer to an array of parameter value unions, set up
    /// by init() from the ComponentType data.
    ParameterValue *paramVals;
    
    /// set a parameter's value from an encoded value and type code.
    void setParamValue(int paramnum,char code,const char *val){
        if(paramnum>=type->paramct)
            throw SE_NOSUCHPARAM;
        type->params[paramnum]->set(this,code,val);
    }
    
    /// make the component always run when a value for this output
    /// is requested, even if this is done multiple times in the same tick.
    void setOutputRunAlways(int n,bool v){
        runAlways[n] = v;
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
        paramVals = NULL;
        for(int i=0;i<ComponentType::NUMINPUTS;i++){
            inputs[i].c=NULL;
        }
        for(int i=0;i<ComponentType::NUMOUTPUTS;i++){
            runAlways[i]=false;
        }
    }
    
        
    
    /// the patch will deallocate the component slot and detach any inputs feeding from me
    ~Component(){
        printf("shutting down component %p",this);
        if(type){
            // call shutdown in the type
            type->shutdownComponent(this);
            // delete any parameters
            delete[] paramVals;
            type = NULL;
        }
    }
    
    /// run the type's initialisation code, which has to be done after the ctor, because
    /// at that point we don't know what the type is.
    void init(){
        if(!type)
            throw Exception("cannot init component with no type");
        
        type->initComponent(this);
        // set up the parameter value array
        paramVals = new ParameterValue [type->paramct];
        for(int i=0;i<type->paramct;i++){
            type->params[i]->setDefault(paramVals+i);
        }
    }
    
    
    
    
    /// the slot number - i.e. the index of the private runtime data in the patch instance.
    
    int slot;
    void setSlot(int s){
        if(slot!=-1)
            throw Exception("slot type already assigned");
        slot = s;
    }
    
    ComponentType *type; //!< the component type
    
    /// if this is set for a given output, the component will run for that 
    /// output whether it has already done so for this tick or not.
    bool runAlways[ComponentType::NUMOUTPUTS];
    
    /// set up the component according to it's type; completes
    /// the initialisation
    
    void setType(ComponentType *t){
        if(type != NULL)
            throw Exception("component type already assigned");
        type = t;
    }
    
    const char *getExtraText(){
        static char buf[256];
        return type->getExtraText(this,buf);
    }
};



#endif /* __COMPONENT_H */
