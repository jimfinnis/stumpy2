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

class Parameter {
public:
    /// set the value given the encoded string
    /// 
    virtual void setValue(
                  char code, //!< the 'ID code' for the parameter type
                  const char *s //!< the actual encoded value
                  ) = 0;
    
    /// check that the code matches the ID code
    void checkCode(char actualCode,char desiredCode){
        if(actualCode!=desiredCode)
            throw SE_BADPARAMTYPE;
    }
    
    int idx;
};

class IntParameter : public Parameter {
private:
    int value;
    int minVal,maxVal;
public:
    IntParameter(int mn,int mx){
        minVal = mn;
        maxVal = mx;
    }
    
    virtual void setValue(char code, const char *s){
        checkCode(code,'i');
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
    FloatParameter(float mn,float mx){
        minVal = mn;
        maxVal = mx;
    }
    
    virtual void setValue(char code,const char *s){
        checkCode(code,'f');
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
    
    virtual void setValue(char code,const char *s){
        checkCode(code,'b');
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
