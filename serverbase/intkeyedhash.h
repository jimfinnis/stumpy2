#ifndef __INTKEYEDHASH_H
#define __INTKEYEDHASH_H

/**
 * @file
 * Hash : An implementation of a hash table keyed on unsigned integer,
 * based on the Python dictionary. See Hash for a version with a general
 * key. The code is largely identical, but this version is faster. I
 * don't like the idea of code duplication on this scale, but it's
 * not really possible any other way.
 * 
 * Setting an item will run the constructor. Deleting an item will run the destructor (as
 * will emptying/destroying the table.) Overwriting an item will destroy the old item,
 * then construct the new.
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <new>
#include "iterator.h"



// 5 in original
#define PERTURB_SHIFT 5
// 32 in original
#define INITIAL_SIZE 32
// 4 in original
#define RESIZE_FACTOR	4

// 2/3 in original
#define RESIZE_THRESHOLD_NUMERATOR 2
#define RESIZE_THRESHOLD_DENOMINATOR 3

//#define DEBUG 1

#define HSH_FREE    0 
#define HSH_USED    1
#define HSH_DELETED 2

/// an individual slot in the property hash table.. do not new this, malloc it instead!

template <class T>struct IntKeyedHashEnt {
    uint32_t k; 	//!< the key 
    int s;		//!< state: free, used or deleted?
    T v;		//!< the value
    
    /// initialiser; we don't want to run a constructor on the entry itself
    void init(){
        k=0;
        s=HSH_FREE;
    }
    
    void destroy(){
        if(s == HSH_USED)
            v.~T(); // actually destruct the item
        s = HSH_DELETED;
    }
        
};


/// templated destroy so we can run the dtor
template <class T> inline void destroy(T& x) { x.~T();}

/// This is an implementation of a hash table in which the keys are 
/// unsigned integers. It's based on the Python dictionary, from notes
/// in Beautiful Code. There's also a good description of the Python
/// implementation at http://www.laurentluce.com/?p=249
/// Also the original source code is in dictobject.c
///
/// This is a much simpler version than that in Hash because the
/// keys are simple unsigned integers.
///
///

template <class T> class IntKeyedHash {
    
    /// this initialises the table but does not run
    /// constructors on its members - that's done for each
    /// element when it's added.
    void initTable(){
        int size = mask+1;
        table = (IntKeyedHashEnt<T> *)malloc(sizeof(IntKeyedHashEnt<T>)*size);
        for(int i=0;i<size;i++){
            table[i].init();
        }
    }
        
public:
    
    IntKeyedHash(){
#ifdef DEBUG
        miss=0;
#endif
        mask = INITIAL_SIZE-1;
        initTable();
        used=0;
        fill=0;
        recalcresizethreshold();
    }
    
    ~IntKeyedHash(){
        printf("deleting table of %d\n",mask+1);
        free(table);
        printf("deleted\n");
#ifdef DEBUG
//        fprintf(stderr,"misses : %d, size %d\n",miss,mask+1);
#endif
    }
    
    /// empty the hash of all values
    void clear(){
        IntKeyedHashEnt<T> *ent = table;
        for(uint32_t i=0;i<=mask;i++){
            if(ent->s == HSH_USED){
                ent->v.~T();
                ent->s = HSH_FREE;
            }
            ent++;
        }
        used=0;
        fill=0;
    }
    
    /// set a value in the table - returns a value pointer for
    /// you to write to, and will construct the item for you.
    
    virtual  T* set(uint32_t k){
        //printf("set %d to %d, used %d, size %d\n",k,v,used,mask+1);
        
        if(used > resizethreshold){
            //printf("RESIZE!!!!!\n");
            resize();
        }
        
        IntKeyedHashEnt<T> *ent = look(k);
        if(ent->s == HSH_USED){
            // we run the destructor if there was something there
            ent->v.~T();
        }
        
        if(ent->s != HSH_USED){
            // there wasn't a value there before
            if(ent->s == HSH_FREE)
                fill++; //we aren't overwriting a dummy, so increment fill
            ent->k = k;
            ent->s = HSH_USED;
            used++; // increment used
        }
        // now we run the constructor
        return new (&ent->v) T();
    }
    
    /// finds a value in the hash table, returning true and setting
    /// the internal found value pointer if found. If found, the value
    /// can then be retrieved with getval().
    
    virtual bool find(uint32_t k){
        IntKeyedHashEnt<T> *ent = look(k);
        if(ent->s == HSH_USED) {
            v = &ent->v;
            return true;
        }
        else
            return false;
    }
    
    /// get the last value found by find()
    T *getval(){
        return v;
    }
    
    /// delete an item with a given key, returning true if we did it
    bool del(uint32_t k) {
        IntKeyedHashEnt<T> *ent = look(k);
        if(ent->s != HSH_USED)
            return false;
        ent->destroy();
        used--;
        return true;
    }
    
    
    // create the iterator
    class Iterator<T *> *createValueIterator();
    class Iterator<uint32_t> *createKeyIterator();

#ifdef DEBUG
    int miss;
#endif
    // I wish this lot could be private, but the template below needs to
    // see them. And I can't put a friend declaration for the template in,
    // because then that would have to be above this class. And *that* wouldn't work,
    // because it needs things in *this* class. The joy of templates.
    IntKeyedHashEnt<T> *table;
    T *v;
    
    unsigned int used; //!< number of slots occupied by keys
    unsigned int fill; //!< number of slots occupied by keys or dummies (used only if we implement deletion)
    unsigned int mask; //!< hashtable contains mask+1 slots
    unsigned int resizethreshold;
    
    void recalcresizethreshold(){
        resizethreshold = (mask+1)*RESIZE_THRESHOLD_NUMERATOR;
        resizethreshold /= RESIZE_THRESHOLD_DENOMINATOR;
    }
    
    void resize(){
        unsigned int oldsize = mask+1;
        IntKeyedHashEnt<T> *oldtable = table;
        unsigned int minused = used*RESIZE_FACTOR;
              
        uint32_t newsize;
        for(newsize = oldsize; newsize<=minused && newsize>0;newsize<<=1){}
        //printf("resizing to %d\n",newsize);
        
        mask = newsize-1;
        initTable();
        used = 0;
        fill = 0;
        // iterate values, reinserting into new table
        IntKeyedHashEnt<T> *ent=oldtable;
        T *p;
        for(unsigned int i=0;i<oldsize;i++,ent++){
            if(ent->s == HSH_USED){
                //printf("RESIZE SET\n");
                p = set(ent->k);
                *p = ent->v;
            }
        }
        free(oldtable);
        recalcresizethreshold();
        //printf("RESIZE END!\n");
    }
    
    /// scan, looking for either a slot with this key or the
    /// slot where this key would go
    
    IntKeyedHashEnt<T> *look(uint32_t k){
        register unsigned int slot = k & mask;
        register IntKeyedHashEnt<T> *ent = table+slot;
        register IntKeyedHashEnt<T> *freeslot;
        if(ent->s==HSH_FREE || ent->k == k)
            return ent;
        if(ent->s == HSH_DELETED)
            freeslot = ent;
        else
            freeslot = NULL;
        
        for(unsigned int perturb = k;;perturb>>=PERTURB_SHIFT){
#ifdef DEBUG
            miss++;
#endif
            slot = (slot<<2)+slot+1+perturb;
            ent = table+(slot&mask);
            if(ent->s == HSH_FREE)
                return freeslot==NULL ? ent : freeslot;
            if(ent->k == k && ent->s!=HSH_DELETED)
                return ent;
            else if(ent->s==HSH_DELETED && freeslot==NULL)
                freeslot = ent;
        }
    }
};

/// IntKeyedHash value iterator - you probably won't access this
/// directly.

template <class T> class IntKeyedHashValueIterator : public Iterator<T *> {
public:
    IntKeyedHashValueIterator(IntKeyedHash<T> *h){
        hash = h;
        ent=NULL;
    }
    
    virtual void first(){
        size=hash->mask+1;
        ent=hash->table;
        idx=0;
        while(idx<size && ent->s != HSH_USED) {idx++;ent++;}
    }
    virtual void next(){
        ent++;idx++;
        while(idx<size && ent->s != HSH_USED) {idx++;ent++;}
    }
    virtual bool isDone() const {
        return idx>=size;
    }
    virtual T *current() {
        if(!ent)
            throw IteratorException("first() not called on iterator");
        if(idx>=size)
            throw IteratorException("iterator out of range");
        return &ent->v;
    }
    
private:
    IntKeyedHash<T> *hash;
    int idx,size;
    IntKeyedHashEnt<T> *ent;
};

template<class T> Iterator<T *> *IntKeyedHash<T>::createValueIterator() {
    return new IntKeyedHashValueIterator<T>(this);
};



/// IntKeyedHash key iterator, used by PropertyKeyIterator

template <class T> class IntKeyedHashKeyIterator : public Iterator<uint32_t> {
public:
    IntKeyedHashKeyIterator(IntKeyedHash<T> *h){
        hash = h;
    }
    
    virtual void first(){
        size=hash->mask+1;
        ent=hash->table;
        idx=0;
        while(idx<size && ent->s != HSH_USED) {idx++;ent++;}
    }
    virtual void next(){
        ent++;idx++;
        while(idx<size && ent->s != HSH_USED) {idx++;ent++;}
    }
    virtual bool isDone() const {
        return idx>=size;
    }
    virtual uint32_t current() {
        if(!ent)
            throw IteratorException("first() not called on iterator");
        return ent->k;
    }
    
private:
    IntKeyedHash<T> *hash;
    int idx,size;
    IntKeyedHashEnt<T> *ent;
};

template<class T> Iterator<uint32_t> *IntKeyedHash<T>::createKeyIterator() {
    return new IntKeyedHashKeyIterator<T>(this);
};


    
#endif /* __INTKEYEDHASH_H */
