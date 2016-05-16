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
