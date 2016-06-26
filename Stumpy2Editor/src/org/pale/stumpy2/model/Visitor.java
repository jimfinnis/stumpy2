package org.pale.stumpy2.model;

/**
 * The "visitor" side of the visitor pattern. See Visitable.
 * There's a method here for each sort of thing that we might visit.
 * @author white
 *
 */
public abstract class Visitor {
    /**
     * Visit a Component
     * @param c the component which the visitor is visiting
     */
    abstract public void visitComponent(Component c);
    
    /**
     * The visitor can set this value inside visitComponent. It can then
     * be examined after the visitations are complete.
     */
    public Component rv;
}
