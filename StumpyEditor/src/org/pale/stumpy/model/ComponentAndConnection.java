package org.pale.stumpy.model;

import java.awt.Point;

/**
 * Data on whether a click was on a component, whether it was on an input or
 * output, and if so, which.
 * 
 * @author white
 * 
 */

public class ComponentAndConnection {
    /**
     * What sort of click a component click was
     * 
     * @author white
     * 
     */
    public enum ComponentClickType {
        /**
         * Click was not on a connection, just on the body of the component
         */
        NO_CONNECTION,
        /**
         * Click was on an input
         */
        INPUT,
        /**
         * Click was on an output
         */
        OUTPUT
    };

    /**
     * The component in question
     */
    public Component c;

    /**
     * Index of the connection, which is irrelevant if type == NOT_ON_CONNECT
     */
    public int index;

    /**
     * NOT_ON_CONNECTION means only the component is relevant ON_INPUT means
     * we're dealing with a connection, and it's an input connection ON_OUTPUT
     * means we're dealing with a connection, and it's an output connection
     */
    public ComponentClickType type;

    /**
     * Constructor
     * 
     * @param c
     *            the component in question
     * @param type
     *            the type of the data (typically this class is used to provide
     *            data about a click on a component which may be on the
     *            component body, on an input, or on an output)
     * @param index
     *            the index of any connection
     */
    public ComponentAndConnection(Component c, ComponentClickType type,
            int index) {
        this.c = c;
        this.type = type;
        this.index = index;
    }

    /**
     * Simpler constructor for non-connection clicks.
     * 
     * @param c
     */
    public ComponentAndConnection(Component c) {
        this(c, ComponentClickType.NO_CONNECTION, -1);
    }

    /**
     * Disconnect any connection represented by this object
     * 
     * @param p
     *            the patch the component is inside
     * @throws ConnectionOutOfRangeException
     */
    public void disconnect(Patch p) throws ConnectionOutOfRangeException {
        if (type == ComponentClickType.INPUT)
            p.unlinkInput(c, index);
        else if (type == ComponentClickType.OUTPUT)
            p.unlinkOutput(c, index);

    }

    /**
     * If this is a connection, return the point
     * 
     * @return point or null if there's a problem
     * @throws ConnectionOutOfRangeException 
     */
    public Point getPosition() throws ConnectionOutOfRangeException {
        Point p = null;
        ComponentType t = c.getType();
        if (type == ComponentClickType.INPUT) {
            p = t.getInputPos(index, c);
        } else if (type == ComponentClickType.OUTPUT) {
            p = t.getOutputPos(index, c);
        }
        return p;
    }
}