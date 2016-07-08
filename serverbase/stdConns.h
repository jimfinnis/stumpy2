/**
 * @file stdConns.h
 * @brief Standard connection types (flow,int,float)
 *
 */

#ifndef __STDCONNS_H
#define __STDCONNS_H

#include "model.h"
#include "instances.h"

/// register the standard connection types.
void regStdCons();

class FlowCon : public ConnectionType {
public:
    FlowCon() : ConnectionType(0,"flow",0x000000ff,FLOAT){}
    void getInput(ComponentInstance *ci,int in){
        ci->getInput(in);
    }
    void setOutput(ComponentInstance *ci,int o){
        ConnectionValue& v = ci->output(o);
        v.t = this;
    }
};
extern FlowCon *tFlow;

class FloatCon : public ConnectionType {
public:
    FloatCon() : ConnectionType(1,"float",0x0000ffff,FLOAT){}
    void setOutput(ComponentInstance *ci,int o,float f){
        ConnectionValue& v = ci->output(o);
        v.t = this;
        v.d.f = f;
    }
    
    float getInput(ComponentInstance *ci,int in){
        ConnectionValue& v = ci->getInput(in);
        if(v.t == NULL)return 0;
        if(v.t != this)throw Exception("").
              set("input %s:%d is %s, not %s",ci->component->type->name,
                  in,v.t->name,name);
        return v.d.f;
    }
};
extern FloatCon *tFloat;

class IntCon : public ConnectionType {
public:
    IntCon() : ConnectionType(2,"int",0x009000ff,INT){}
    void setOutput(ComponentInstance *ci,int o,int i){
        ConnectionValue& v = ci->output(o);
        v.t = this;
        v.d.i = i;
    }
    
    int getInput(ComponentInstance *ci,int in){
        ConnectionValue& v = ci->getInput(in);
        if(v.t == NULL)return 0;
        if(v.t != this)throw Exception("").
              set("input %s:%d is %s, not %s",ci->component->type->name,
                  in,v.t->name,name);
        return v.d.i;
    }
};
extern IntCon *tInt;





#endif /* __STDCONNS_H */
