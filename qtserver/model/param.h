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
 * The way parameters work is ODD. Notice that in a component type, when a component
 * is initialised in initComponent() we do something like
 *   c->setParams(pParamFoo=new SomeParam()...)
 * so we set the parameter in the *component*, but also set members in the *type*.
 * The setParams() method actually puts the newly allocated parameters into an array
 * private for each component. BUT they are also set into the component type, so
 * that the last component's parameters act as the prototypes for the parameters of
 * the whole type. Note how this works in IntParameter::get():
 *     int IntParameter::get(Component *c){
 *       IntParameter *p = (IntParameter *)c->params[idx];
 *       return p->value;
 *     }
 * So we call this on whatever is in the *type* (as pParamFoo above), but the it
 * knows its index in the parameter array for the component, and looks up the REAL
 * parameter in the component itself.
 * 
 * This is either really clever or really stupid. I can't make up my mind.
 */

struct Parameter {
    char code; // type code
    const char *name; // name in UI
    /// set the value given the encoded string
    /// 
    virtual void setValue(
                  char code, //!< the 'ID code' for the parameter type
                  const char *s //!< the actual encoded value
                  ) = 0;
    
    /// check that the code matches the ID code
    void checkCode(char actualCode){
        if(actualCode!=code)
            throw SE_BADPARAMTYPE;
    }
    
    /// return a static description string, for sending to the client
    virtual const char *getDesc()=0;
    
    Parameter(const char *n){
        name = n;
    }
    
    virtual ~Parameter(){}
    
    int idx;
};

class IntParameter : public Parameter {
private:
    int value;
    int minVal,maxVal;
public:
    IntParameter(const char *n,int mn,int mx,int init) : Parameter(n){
        code = 'i';
        minVal = mn;
        maxVal = mx;
        value = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"i:%s:%d:%d:%d",name,
                minVal,maxVal,value);
        return buf;
    }
    
    
    virtual void setValue(char c, const char *s){
        checkCode(c);
        int v = atoi(s);
        if(v<minVal || v>maxVal)
            throw SE_PARAMOUTOFRANGE;
        value = v;
    }
    
    int get(Component *c);
};

class EnumParameter : public Parameter {
private:
    int value;
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
        value = ini;
    }
    
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"e:%s:%d:%d",name,count,value);
        return buf;
    }
    
    int getCount(){
        return count;
    }
    
    const char *getString(int i){
        return strings[i];
    }
    
    virtual void setValue(char c, const char *s){
        checkCode(c);
        int v = atoi(s);
        if(v<0 || v>=count)
            throw SE_PARAMOUTOFRANGE;
        value = v;
    }
    
    int get(Component *c);
};


class FloatParameter : public Parameter {
private:
    float value;
    float minVal,maxVal;
public:
    FloatParameter(const char *n,float mn,float mx,float init)
     : Parameter(n){
        code = 'f';
        minVal = mn;
        maxVal = mx;
        value = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"f:%s:%f:%f:%f",name,
                minVal,maxVal,value);
        return buf;
    }
    
    virtual void setValue(char c,const char *s){
        checkCode(c);
        float v = atof(s);
        if(v<minVal || v>maxVal)
            throw SE_PARAMOUTOFRANGE;
        value = v;
    }
    
    float get(Component *c);
};

class BoolParameter : public Parameter {
private:
    bool value;
public:
    
    BoolParameter(const char *n,bool init) : Parameter(n){
        code = 'b';
        value = init;
    }
    
    virtual const char *getDesc(){
        static char buf[1024];
        sprintf(buf,"b:%s:%c",name,
                value?'y':'n');
        return buf;
    }
    
    virtual void setValue(char c,const char *s){
        checkCode(c);
        switch(*s){
        case 'y':value=true;break;
        case 'n':value=false;break;
        default:
            throw SE_PARAMOUTOFRANGE;
            break;
        }
    }
    
    bool get(Component *c);
};





#endif /* __PARAM_H */
