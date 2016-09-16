/**
 * @file generators.h
 * @brief  Brief description of file.
 *
 */

#ifndef __GENERATORS_H
#define __GENERATORS_H

#include "util.h"

class Generator {
protected:
    int len,depth;
    int *seq;
    int cur,val;
    bool symmetric;
    bool didcycle;
    unsigned int randstate;
public:
    Generator(int l,int d,bool sym){
        randstate = 28; // random seed (Catrin picked it!)
        len=l;depth=d;
        seq = new int[len];
        cur = 0;
        symmetric = sym;
        // call reset after this in your own ctor
    }
    
    virtual ~Generator(){
        delete [] seq;
    }
    
    virtual void reset()=0; // this actually makes the seq
    
    // just get the next plump itemry! We have to reset
    // by hand, between each run, but the first MUST
    // be done for us.
    int next(){
        printf("%p - cur %d len %d\n",this,cur,len);
        val = seq[cur++];
        cur %= len;
        didcycle = (cur==0);
        return val;
    }
    
    // return true if the previous next() started a new cycle (will
    // not trigger on first next() )
    bool cycled(){
        return didcycle;
    }
    
    // just restart the same generated sequence, and indicate
    // that we cycled (cos we sort of did)
    void rewind(){
        cur=0;
        didcycle=true;
    }
        
    
    void postReset(){
        // this is a bit inefficient as we're generating twice
        // the sequence for symmetric data
        
        if(symmetric){
            for(int i=len/2;i<len;i++){
                seq[i]=seq[len-i-1];
            }
        }
    }
    
    
    int get(){
        return val;
    }
};

class Morse : public Generator {
    int *prevseq;
    int perms[100];
    int permct;
public:
    Morse(int l,int d,bool s,const char *p) : Generator(l,d,s) {
        prevseq = new int[len];
        printf("dep %d\n",d);
        if(p){
            for(const char *q=p;*q;q++){
                int nn;
                if(*q>='a')
                    nn = (*q-'a')+10;
                else
                    nn = *q-'0';
                perms[q-p]=nn;
            }
            permct=strlen(p);
        } else {
            permct=depth;
            // this is for the "default" Thue-Morse sequence
            for(int i=0;i<depth;i++){
                perms[i]=i;
            }
        }
        reset(); // get initial data
    }
    
    virtual ~Morse(){
        delete [] prevseq;
    }
    
    // this would normally just generate the same sequence again,
    // and that's OK - but what we really want is a new sequence.
    // To do that, we'll shuffle the perms. This is deterministic,
    // we use a 
    
    virtual void reset(){
        int templen;
        
        shuf<int>(perms,permct,&randstate);
        
        // seed value 
        prevseq[0]=perms[0];
        int plen=1;
        for(;;){
            // generate a new sequence from the previous
            int newlen=0;
            for(int i=0;i<plen;i++){
                for(int j=0;j<depth;j++){
                    if(newlen==len)
                        goto stop;
                    int base = prevseq[i]+perms[j%permct];
                    seq[newlen++]=base%depth;
                }
            }
            // copy into prevseq
            for(int i=0;i<newlen;i++)
                prevseq[i]=seq[i];
            plen=newlen;
            
        }
stop:
        postReset();
    }
    
};

#endif /* __GENERATORS_H */
