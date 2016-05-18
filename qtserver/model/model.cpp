/**
 * @file
 * Model code, but not the graphics - how the patches, components etc. tie together.
 * Most of this will be in model.h.
 * 
 */

#include <stdio.h>
#include <stdarg.h>

#include "model.h"
LinkedList<ComponentType,0> *ComponentType::types=NULL;
ConnectionValue ComponentInstance::noData;

Patch::~Patch(){
    delete [] freeList;
    // delete instances
    
    for(PatchInstance *q,*p = instances.head();p;p=q){
        q = instances.next(p);
        delete p;
    }
    valid = false;
}



Component *Patch::createComponent(uint32_t id,const char *type)
{
    if(components.find(id))
        throw SE_ALREADY;
    
    ComponentType *t = ComponentType::getType(type);
    
    Component *c = components.set(id);
    c->patch = this;
    int slot = allocateNewComponentSlot();
    c->setSlot(slot);
    
    c->setType(t);
    c->init();
    
    for(PatchInstance *pi = instances.head();pi;pi=instances.next(pi)){
        ComponentInstance *ci = pi->getInstance(slot);
        if(ci->isUsed())
            throw Exception("component instance overwrite");
        ci->init(c,pi);
    }
    
    return c;
}

void Patch::deleteComponent(uint32_t id){
    if(!components.find(id))throw SE_NOSUCHCOMP;
    Component *c = components.getval();
    
    // clear instance data
    
    if(!c->type)
        throw Exception("deleting uninitialised component");
    
    for(PatchInstance *pi = instances.head();pi;pi=instances.next(pi)){
        if(c->slot<0)
            throw Exception("deleting uninitialised component instance");
        ComponentInstance *ci = pi->getInstance(c->slot);
        ci->shutdown();
    }
    
    deallocateComponentSlot(c->slot);
    
    // detach inputs leading from this component in any other component
    
    IteratorPtr<uint32_t> iterator(components.createKeyIterator());
    
    for(iterator->first();!iterator->isDone();iterator->next()){
        uint32_t key = iterator->current();
        if(components.find(key)){
            components.getval()->unlinkInputsFrom(c);
        } else 
            throw IteratorException("deleteComponent loop");
    }
    components.del(id);
}

void Patch::unlinkComponentOutput(Component *c,int output){
    IteratorPtr<uint32_t> iterator(components.createKeyIterator());
    
    for(iterator->first();!iterator->isDone();iterator->next()){
        uint32_t key = iterator->current();
        if(components.find(key)){
            Component *p =  components.getval();
            for(int i=0;i<ComponentType::NUMINPUTS;i++){
                const Component::Input *inp = p->getInput(i);
                if(inp->c == c && inp->output == output)
                    p->unlinkInput(i);
            }
        } else 
            throw IteratorException("deleteComponent loop");
    }
}

PatchInstance *Patch::instantiate(){
    // create the instance 
    PatchInstance *pi = new PatchInstance(this);
    
    // iterate over the components
    IteratorPtr<uint32_t> iterator(components.createKeyIterator());
    for(iterator->first();!iterator->isDone();iterator->next()){
        uint32_t key = iterator->current();
        if(components.find(key)){
            Component *c = components.getval();
            // for each one, get the instance data
            ComponentInstance *ci = pi->getInstance(c);
            // and initialise
            ci->init(c,pi);
        } else {
            throw IteratorException("instantiation loop");
        }
    }
    
    // add to the list
    instances.addToTail(pi);
    
    // return the instance
    return pi;
}


PatchInstance::PatchInstance(Patch *p){
    printf("new p-instance %p\n",this);
    patch = p;
    // create the component instances
    instances = new ComponentInstance[Patch::INITIALPOOLSIZE];
    // they are not initialised here; Patch::instantiate() does that.
}

PatchInstance::~PatchInstance(){
    printf("deleting p-instance %p\n",this);
    //TODO make sure any macro components notice if their instance has been deleted
    
    // if this was the instance we're actually running, stop that.
    if(patch->library->active == this){
        patch->library->active = NULL;
        printf("   was active, not any more\n");
    }
    
    patch->removeInstance(this);
    delete [] instances;
}


ComponentInstance *PatchInstance::getInstance(int slot){
    return instances+slot;
}

ComponentInstance *PatchInstance::getInstance(Component *c){
    return instances+c->slot;
}


void PatchLibrary::instantiateAsActive(uint32_t id){
    if(!patches.find(id))
        throw SE_NOSUCHPATCH;
    
    if(active){
        delete active; // this *should* also set active=NULL
    }
    
    active = patches.getval()->instantiate();
}

void PatchInstance::run(){
    // scan the components, looking for outputs
    
    // iterate over the components
    IntKeyedHash<Component> *clist= &patch->components;
    
    IteratorPtr<uint32_t> iterator(clist->createKeyIterator());
    
    for(iterator->first();!iterator->isDone();iterator->next()){
        uint32_t key = iterator->current();
        if(clist->find(key)){
            Component *c = clist->getval();
            if(c->type->isRoot){
                ComponentInstance *ci = getInstance(c);
                // just need to get one output - any output -
                // to process a root component
                c->type->run(ci,0);
            }
        } else {
            throw Exception("run loop iterator problem");
        }
    }
    
}


void ComponentType::setParams(Parameter *p,...){
    va_list ap;
    va_start(ap,p);
    paramct=0;
    
    while(p){
        addParameter(p);
        p = va_arg(ap,Parameter *);
    }
    va_end(ap);
}



/*
 * Parameter getters and setters
 *
 */

void IntParameter::set(Component *comp,char c, const char *s){
    checkCode(c);
    int v = atoi(s);
    if(v<minVal || v>maxVal)
        throw SE_PARAMOUTOFRANGE;
    comp->paramVals[idx].i = v;
}
int IntParameter::get(Component *c){
    return c->paramVals[idx].i;
}

void FloatParameter::set(Component *comp,char c, const char *s){
    checkCode(c);
    float v = atof(s);
    if(v<minVal || v>maxVal)
        throw SE_PARAMOUTOFRANGE;
    comp->paramVals[idx].f = v;
}
float FloatParameter::get(Component *c){
    return c->paramVals[idx].f;
}

void BoolParameter::set(Component *comp,char c, const char *s){
    checkCode(c);
    bool v;
    switch(*s){
    case 'y':v=true;break;
    case 'n':v=false;break;
    default:
            throw SE_PARAMOUTOFRANGE;
        break;
    }
    comp->paramVals[idx].b = v;
}    
bool BoolParameter::get(Component *c){
    return c->paramVals[idx].b;
}

void EnumParameter::set(Component *comp,char c, const char *s){
    checkCode(c);
    int v = atoi(s);
    if(v<0 || v>=count)
        throw SE_PARAMOUTOFRANGE;
    comp->paramVals[idx].i = v;
}
int EnumParameter::get(Component *c){
    return c->paramVals[idx].i;
}

