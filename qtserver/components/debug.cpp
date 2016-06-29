/**
 * @file debug.cpp
 * @brief  Brief description of file.
 *
 */

#include "serverbase/model.h"

class PrintNumComponent : public ComponentType {
public:
    PrintNumComponent() : ComponentType("PrintNum","maths") {
        setInput(0,T_FLOAT,"x");
        setOutput(0,T_FLOW,"flow");
    }
    
   virtual void run(ComponentInstance *ci,int out){
       Component *c = ci->component;
       printf("%f\n",ci->getInput(0).f);
        
    }
};

static PrintNumComponent reg;
