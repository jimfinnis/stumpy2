/**
 * @file
 * Component parameter types
 *
 */

#ifndef __PARAM_H
#define __PARAM_H

#include <stdlib.h>
#include "errors.h"

class Component;

/**
 * 
 */

/// parameter values, stored in an array in the Component,
/// indexed by the idx in the Parameter in the ComponentType.
union ParameterValue {
    int i;
    float f;
    bool b;
};

/// this describes the parameter, and exists in the component type.
/// Each parameter has an index, which indexes the ParameterValue
/// array in the component itself. ParameterValue is a union - the
/// element accessed depends on the param type.

struct Parameter {
    char code; // type code
    const char *name; // name in UI
    
    /// check that the code matches the ID code
    void checkCode(char actualCode){
        if(actualCode!=code)
            throw SE_BADPARAMTYPE;
    }
    
    /// return a static description string, for sending to the client
    virtual const char *getDesc()=0;
    
    /// set the value of the parameter in a component from an
    /// encoded string from the client
    virtual void set(Component *comp,char c, const char *s)=0;
    
    /// set a parameter value to the default for this parameter
    virtual void setDefault(ParameterValue *v)=0;
    
    Parameter(const char *n){
        name = n;
    }
    
    // index of the parameter inside the Component AND ComponentType
    // parameter arrays
    
    int idx; 
};

class IntParameter : public Parameter {
private:
    int initval;
    int minVal,maxVal;
public:
    IntParameter(const char *n,int mn,int mx,int init) : Parameter(n){
        code = 'i';
        minVal = mn;
        maxVal = mx;
        initval=init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"i:%s:%d:%d:%d",name,
                minVal,maxVal,initval);
        return buf;
    }
    
    
    virtual void setDefault(ParameterValue *v){
        v->i = initval;
    }
    virtual void set(Component *comp,char c, const char *s);
    
    int get(Component *c);
};

class EnumParameter : public Parameter {
private:
    int initval;
    int count; // number of values
    const char **strings; // string data
public:
    /// s is a null-terminated array of strings
    EnumParameter(const char *n,const char **s,int ini) : Parameter(n){
        code = 'e';
        count = 0;
        while(s[count])count++;
        printf("String count: %d\n",count);
        strings = s;
        initval = ini;
    }
    
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"e:%s:%d:%d",name,count,initval);
        return buf;
    }
    
    int getCount(){
        return count;
    }
    
    const char *getString(int i){
        return strings[i];
    }
    
    virtual void setDefault(ParameterValue *v){
        v->i = initval;
    }
    virtual void set(Component *comp,char c, const char *s);
    int get(Component *c);
};


class FloatParameter : public Parameter {
private:
    float initval;
    float minVal,maxVal;
public:
    FloatParameter(const char *n,float mn,float mx,float init)
     : Parameter(n){
        code = 'f';
        minVal = mn;
        maxVal = mx;
        initval = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"f:%s:%f:%f:%f",name,
                minVal,maxVal,initval);
        return buf;
    }
    
    virtual void setDefault(ParameterValue *v){
        v->f = initval;
    }
    
    virtual void set(Component *comp,char c, const char *s);
    
    float get(Component *c);
};

class BoolParameter : public Parameter {
private:
    bool initval;
public:
    
    BoolParameter(const char *n,bool init) : Parameter(n){
        code = 'b';
        initval = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"b:%s:%c",name,
                initval?'y':'n');
        return buf;
    }
    
    virtual void set(Component *comp,char c, const char *s);
    
    virtual void setDefault(ParameterValue *v){
        v->b = initval;
    }
    
    bool get(Component *c);
};





#endif /* __PARAM_H */