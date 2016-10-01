# Adding components
Each component is represented by a singleton object referred to as
the "type object": the actual components are all instances of Component,
with an associated ComponentInstance for each running component in the
active patch. Adding a component involves writing a new component type
object, and creating a single instance of it which will auto-register
it with the server at startup.

Here's the Add component, which adds two numbers having added 
constants and multiplied them by other constants first:

```c++
// this includes all details of the stumpy data model
#include "model.h"

// out component: a subclass of ComponentType

class AddComponent : public ComponentType {
public:
    // the constructor just initialises the name and category
    
    AddComponent() : ComponentType("add","maths"){}
    
    // init() sets up input/output types and parameters; it's
    // only called once.
    
    virtual void init() {
        setInput(0,tFloat,"x");
        setInput(1,tFloat,"y");
        setOutput(0,tFloat,"x+y");
        
        // look up the various parameter constructor declarations in
        // serverbase/param.h
        
        setParams(
                     pAdd1 = new FloatParameter("add 1",-100,100,0),
                     pMul1 = new FloatParameter("mul 1",-100,100,1),
                     pAdd2 = new FloatParameter("add 2",-100,100,0),
                     pMul2 = new FloatParameter("mul 2",-100,100,1),
                     NULL
                     );
    }
    
    // this is called by each running component instance, for
    // each output which needs recalculating. It takes the instance
    // and the output number (there's only one output here so we
    // can ignore it).
    
    virtual void run(ComponentInstance *ci,int out){

        // get the actual component, which has the parameters
        Component *c = ci->component;

        // note how we use tFloat->getInput(ci,n) to get an input
        // and param->get(c) to get a parameter value
                
        float a = (tFloat->getInput(ci,0)+pAdd1->get(c))*pMul1->get(c);
        float b = (tFloat->getInput(ci,1)+pAdd2->get(c))*pMul2->get(c);

        // and set the output to the results
        tFloat->setOutput(ci,0,a+b);
    }
    
private:
    // the parameter specifications - not their values, they
    // are stored in each component
    FloatParameter *pAdd1,*pMul1,*pAdd2,*pMul2;
};

// the single instance
static AddComponent addreg;
```

Some components need private data for each instance, such
as the Clock component in the music app. This outputs regular
ticks, so it needs to know when the last tick happened.
To do this, we need to override the normally empty methods
for handling instance initialisation to create and destroy
our private data, and modify run() to get access to it:

```c++
// ... the rest of the class ...
    virtual void initComponentInstance(ComponentInstance *c){
        MyPrivateData *d = new MyPrivateData();
        c->privateData = (void *)d;
        d->start = Time::now();
        for(int i=0;i<NUMOUTS;i++)
            d->prevq[i]=-1;
    }
    
    virtual void shutdownComponentInstance(ComponentInstance *c){
        delete ((MyPrivateData *)c->privateData);
    }
    
    virtual void run(ComponentInstance *ci,int out){
        MyPrivateData *d = (MyPrivateData *)ci->privateData;
        Component *c = ci->component;
        //... the rest of the run method ...
    }
    // ... the rest of the class
```

Have a good look through the code to see how things work.

# Writing applications
If you want to write a new application (i.e. a new server type
with new components), you just need to write a whole load of 
components and a main file something like this:

```c++
#include <unistd.h>
#include "model.h"
#include "controller.h"
#include "server.h"

int main(int argc,char *argv[]){
    // initialisation goes here...
    
    Server server(65111);
    PatchLibrary lib;
        
    server.setListener(new Controller(&lib,&server));
    for(;;){
        if(!server.process())break;
        lib.run();
        // .. other "every update" code goes here
        usleep(1000);
    }
}
```
