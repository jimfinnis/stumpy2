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

#define ENVSIZE 4
struct Envelope {
    float times[ENVSIZE];
    float levels[ENVSIZE];
};


/**
 * 
 */

/// parameter values, stored in an array in the Component,
/// indexed by the idx in the Parameter in the ComponentType.
/// A bit hacky because of the string - imagine deleting it
/// if it's of the wrong type!
struct ParameterValue {
    ParameterValue(){
        s = NULL;
    }
    ~ParameterValue(){
        if(s)free((void *)s);
    }
    const char *getstr(){
        return s;
    }
    void setstr(const char *str){
        if(s)free((void *)s);
        s=strdup(str);
    }
    
    union {
        // trivial elements
        int i;
        float f;
        bool b;
        Envelope env;
    } d;
private:
    const char *s; // reallocated every time set
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
        v->d.i = initval;
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
        v->d.i = initval;
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
        v->d.f = initval;
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
        v->d.b = initval;
    }
    
    bool get(Component *c);
};

class StringParameter : public Parameter {
private:
    const char *initval;
public:
    
    StringParameter(const char *n,const char* init) : Parameter(n){
        code = 's';
        initval = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"s:%s:%s",name,initval);
        return buf;
    }
    
    virtual void set(Component *comp,char c, const char *s);
    
    virtual void setDefault(ParameterValue *v){
        v->setstr(initval);
    }
    
    const char *get(Component *c);
};


class EnvelopeParameter : public Parameter {
public:
    EnvelopeParameter(const char *n) : Parameter(n) {
        code = 'E';
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"E:%s",name);
        return buf;
    }
    
    virtual void setDefault(ParameterValue *v){
        for(int i=0;i<ENVSIZE;i++){
            v->d.env.levels[i]=0;
            v->d.env.times[i]=0;
        }
        v->d.env.levels[0]=1;
        v->d.env.levels[1]=1;
        v->d.env.levels[2]=0;
        v->d.env.times[0]=0;
        v->d.env.times[1]=1;
        v->d.env.times[2]=2;
    }
    
    virtual void set(Component *comp,char c,const char *s);
    Envelope& get(Component *c);
};



#endif /* __PARAM_H */
