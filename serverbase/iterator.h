/**
 * @file
 * Provides definitions for the Iterator pattern -  see \ref iters for more details.
 * 
 */

#ifndef __ITERATOR_H
#define __ITERATOR_H

#include "util/exception.h"

/// an exception for iterators - see exception.h

class IteratorException : public Exception {
public:
    IteratorException(const char *t) : Exception("iterator error",t){}
};
        


/// the base iterator interface, providing the type-invariant first(), next() and isDone() method definitions.

class BaseIterator {
public:
    virtual void first()=0;
    virtual void next()=0;
    virtual bool isDone() const =0;
};    

/// abstract class defining the Iterator interface - any iterable object must provide
/// a subclass of this, returned by some iterator creation method. Do not use directly,
/// use an IteratorPtr if you can - that will manage creation and deletion of the
/// iterator without any overhead [GangOfFour, p267]. See \ref iters for more details.

template <class T> class Iterator : public BaseIterator{
public:
    virtual T current() = 0;
    /// we need a virtual destructor so that subclass destructors run correctly
    virtual ~Iterator(){}
};

/** Iterator manager for wrapping Iterators in a memory-safe way.
 * 
 * this class manages Iterators. Use it like this:
 * @code
 * IteratorPtr<Fish *> iterator(list->createIterator());
 * ...
 * @endcode
 */

template <class T> class IteratorPtr {
public:
    IteratorPtr(Iterator<T>* i) : _i(i) {}
    ~IteratorPtr() { delete _i;}
    Iterator<T>* operator->() {return _i;}
    Iterator<T>& operator*() {return *_i;}
private:
    // disallow copy and assignment
    IteratorPtr(const IteratorPtr&);
    IteratorPtr& operator=(const IteratorPtr&);
    
    Iterator<T> *_i;
};

#endif /* __ITERATOR_H */
