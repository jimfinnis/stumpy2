/**
 * @file bitfield.h
 * @brief  Brief description of file.
 *
 */

#ifndef __BITFIELD_H
#define __BITFIELD_H

/// a simple 128-bitfield - yes, I know there's a bitfield
/// built-in. Don't ask.

#include <stdint.h>

class BitField {
private:
    uint32_t bits[4];
public:
    /// can't have a ctor because it won't go in the union
    /// without complicating matters.
    void clear(){
        for(int i=0;i<4;i++)bits[i]=0;
    }
    bool get(int b) const{
        uint32_t i = bits[b>>5];
        return (i & (1<<(b&0x1f)))!=0;
    }
    void set(int b,bool v){
        uint32_t *i = bits+(b>>5);
        if(v){
            *i |= 1<<(b&0x1f);
        } else {
            *i &= ~(1<<(b&0x1f));
        }
    }
};


#endif /* __BITFIELD_H */
