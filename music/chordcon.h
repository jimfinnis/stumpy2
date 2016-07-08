/**
 * @file chordcon.h
 * @brief  Brief description of file.
 *
 */

#ifndef __CHORDCON_H
#define __CHORDCON_H

class ChordCon : public ConnectionType {
public:
    ChordCon() : ConnectionType(10,"chord",0xff0000ff,BITFIELD){}
    
    BitField getInput(ComponentInstance *ci,int in){
        ConnectionValue& v = ci->getInput(in);
        if(v.t == NULL)return BitField();
        if(v.t != this)throw Exception("").
              set("input %s:%d is %s, not %s",ci->component->type->name,
                  in,v.t->name,name);
        return v.d.b;
    }
    void setOutput(ComponentInstance *ci,int o,BitField b){
        ConnectionValue& v = ci->output(o);
        v.t = this;
        v.d.b = b;
    }
};
extern ChordCon *tChord;


#endif /* __CHORDCON_H */
