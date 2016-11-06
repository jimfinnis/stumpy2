/**
 * @file util.h
 * @brief  Brief description of file.
 *
 */

#ifndef __UTIL_H
#define __UTIL_H

// fisher-yates shuffle, using either the standard PRNG
// or one which holds state (rand_r).
template<class T> void shuf(T *s,int len,unsigned int *randstate=NULL){
    for(int i=len-1;i>0;i--){
        int j = (randstate?rand_r(randstate):rand())%(i+1);
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

inline int hexdigit(char c){
    return (c>='a')?(c-'a')+10:c-'0';
}


#endif /* __UTIL_H */
