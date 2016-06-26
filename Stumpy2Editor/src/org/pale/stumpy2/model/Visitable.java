package org.pale.stumpy2.model;

/**
 * The "visitable" side of the Visitor pattern
 * @author white
 *
 */
public interface Visitable {
    /**
     * Called by visitors when we want this object to do something.
     * @param v the visitor we are being visited by 
     */
    void accept(Visitor v);
}
