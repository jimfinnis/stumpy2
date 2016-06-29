/**
 * @file debug.cpp
 * @brief  Brief description of file.
 *
 */

#include "serverbase/model.h"

class PrintNumComponent : public ComponentType {
public:
    PrintNumComponent() : ComponentType("PrintNum","maths"){}
    virtual void init() {
        setInput(0,tFloat,"x");
        setOutput(0,tFlow,"flow");
    }
    
   virtual void run(ComponentInstance *ci,int out){
       Component *c = ci->component;
       printf("%f\n",tFloat->getInput(ci,0));
    }
};

static PrintNumComponent reg;
