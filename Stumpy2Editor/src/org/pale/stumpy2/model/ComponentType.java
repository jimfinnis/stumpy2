package org.pale.stumpy2.model;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JPanel;

import org.pale.stumpy2.model.ComponentAndConnection.ComponentClickType;

/**
 * Contains information about the type of a component. Each Component has a link
 * to one of these. Information includes: name, size of box on screen;
 * connections, with types, names and positions. The connection positions are
 * automatically calculated (although I may make this overridable.)
 * There's a lot of "view" stuff in here, simply because separating out the graphics code
 * would be too confusing. For me, anyway.
 * 
 * 
 * 
 * @author white
 * 
 */
public class ComponentType {
    /** size of a connection pad on screen for drawing purposes */
    public static final int CONNECTION_WIDTH = 10;

    /** the size of a connection pad on the screen for click detection purposes! */
    public static final int CONNECTION_DETECT_WIDTH = 20;

	private static final Color LIGHT_GREY = Color.decode("#c0c0c0");

	private static final int DEFAULTHEIGHT = 30;

    /** The name of this component type */
    private String name;
    
    /**
     * Category of the component
     */
    private String category;
    
    public String getCategory(){
        return category;
    }

    /**
     * getter for name, there is no setter
     * 
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * Information about a connection - connection type and name, and also position
     * relative to top left of image
     */
    private class ConnectionInfo {
        ConnectionType type;
        String name;
        int x, y;

        boolean intersects(Point componentTopLeft, Point p) {
            Rectangle r = new Rectangle(componentTopLeft.x + x
                    - CONNECTION_DETECT_WIDTH / 2, componentTopLeft.y + y
                    - CONNECTION_DETECT_WIDTH / 2, CONNECTION_DETECT_WIDTH,
                    CONNECTION_DETECT_WIDTH);
            return r.contains(p);
        }

        ConnectionInfo(ConnectionType type, String name) {
            this.type = type;
            this.name = name;
        }

        public void setPosition(int x, int y) {
            this.x = x;
            this.y = y;
        }

        /**
         * Draw a connection for a component at cx,cy
         * 
         * @param g
         * @param cx
         * @param cy
         */
        public void draw(Graphics g, int cx, int cy) {
            g.setColor(type.getCol());
            int xx = cx + x - CONNECTION_WIDTH / 2;
            int yy = cy + y - CONNECTION_WIDTH / 2;
            g.fillRect(xx, yy, CONNECTION_WIDTH, CONNECTION_WIDTH);

        }
    }
    
    /** A list of the inputs we have - gets changed to an array later */
    private List<ConnectionInfo> inputList = new LinkedList<ConnectionInfo>();
    /** A list of the outputs we have - gets changed to an array later */
    private List<ConnectionInfo> outputList = new LinkedList<ConnectionInfo>();
    /** size of box on screen */
    private Dimension size;

    public Dimension getSize() {
        return size;
    }

    /**
     * Initialise a component type
     * 
     * @param n
     *            name
     * @param catName
     *            category name
     * @param width
     *            width on screen
     * @param height
     *            height on screen
     */
    public ComponentType(String n, String catName, int width, int height) {
        this.name = n;
        this.category = catName;
        this.size = new Dimension(width, height>0 ? height : DEFAULTHEIGHT);
        
    }

    /**
     * Add a new input
     * 
     * @param v
     *            type of the input to add
     * @param name
     *            name of input
     */
    public void addInput(ConnectionType v, String name) {
        inputList.add(new ConnectionInfo(v, name));
    }

    /**
     * Add a new output
     * 
     * @param v
     *            type of the output to add
     * @param name
     *            name of output
     */
    public void addOutput(ConnectionType v, String name) {
        outputList.add(new ConnectionInfo(v, name));
    }
    

    /**
     * Perform layout, once all connections added - will set their positions.
     */
    public void layout() {
        layoutConnectionSetHorizontally(0, inputList);
        layoutConnectionSetHorizontally((int) (size.getHeight() - 1),
                outputList);

        // layout done, convert to arrays for speed
        inputList = new ArrayList<ConnectionInfo>(inputList);
        outputList = new ArrayList<ConnectionInfo>(outputList);
    }

    /**
     * return how many inputs this component has
     * 
     * @return input count
     */
    public int getInputCount() {
        return inputList.size();
    }

    /**
     * return how many outputs this component type has
     * 
     * @return output count
     */
    public int getOutputCount() {
        return outputList.size();
    }

    /**
    /**
     * Layout a set (well, a list) of connections horizontally at a given y
     * position, distributing them evenly across the width of the object.
     * 
     * @param y
     *            the y position
     * @param set
     *            the set of connections (inputs or outputs)
     */
    private void layoutConnectionSetHorizontally(int y, List<ConnectionInfo> set) {
        double num = set.size();
        double divisionSize = size.getWidth() / num;
        double x = (divisionSize - CONNECTION_WIDTH) / 2.0;

        for (ConnectionInfo info : set) {
            info.setPosition((int) x, y);
            x += divisionSize;
        }

    }

    /**
     * Get the coordinates of one of the inputs of a component
     * 
     * @throws ConnectionOutOfRangeException
     * 
     */
    public Point getInputPos(int i, Component c)
            throws ConnectionOutOfRangeException {
        if (i >= getInputCount())
            throw new ConnectionOutOfRangeException();
        ConnectionInfo info = inputList.get(i);
        return new Point(c.rect.x + info.x, c.rect.y + info.y);
    }

    /**
     * Get the coordinates of one of the outputs of a component
     * @return the position relative to the surface containing the component
     * 
     * @throws ConnectionOutOfRangeException
     * 
     */
    public Point getOutputPos(int i, Component c)
            throws ConnectionOutOfRangeException {
        if (i >= getOutputCount())
            throw new ConnectionOutOfRangeException();
        ConnectionInfo info = outputList.get(i);
        return new Point(c.rect.x + info.x, c.rect.y + info.y);
    }
    
    
    /**
     * Get the type of an input connection
     * @param i the index of the connection
     * @return the type of the connection
     * @throws ConnectionOutOfRangeException 
     */
    public ConnectionType getInputType(int i) throws ConnectionOutOfRangeException{
        if (i >= getInputCount())
            throw new ConnectionOutOfRangeException();
        return inputList.get(i).type;
    }

    /**
     * Get the type of an output connection
     * @param i the index of the connection
     * @return the type of the connection
     * @throws ConnectionOutOfRangeException 
     */
    public ConnectionType getOutputType(int i) throws ConnectionOutOfRangeException{
        if (i >= getOutputCount())
            throw new ConnectionOutOfRangeException();
        return outputList.get(i).type;
    }
    
    
    /**
     * 
     * @return a list of the names of all the input connections
     */
    public List<String> getAllInputNames(){
        List<String> list = new LinkedList<String>();
        for(ConnectionInfo i : inputList){
            list.add(i.name);
        }
        return list;
    }

    /**
     * 
     * @return a list of the names of all the output connections
     */
    public List<String> getAllOutputNames(){
        List<String> list = new LinkedList<String>();
        for(ConnectionInfo i : outputList){
            list.add(i.name);
        }
        return list;
    }

    /**
     * Create a component of this type at a given position
     * 
     * @return a new component
     * @param p the patch in which the component should be created
     * @param pos
     *            position in canvas
     */
    Component create(Point pos) {
        return new Component(this, pos);
    }

    /**
     * Draw the connections to my inputs.
     * 
     * @param g
     * @param selected
     * @param c
     * @throws ConnectionOutOfRangeException 
     */
    void drawConnections(Graphics g, boolean selected, Component c) throws ConnectionOutOfRangeException {
        for (int i = 0; i < getInputCount(); i++) {
            Component.Input inp = c.getInput(i);
            if (inp != null) {
                g.setColor(getInputType(i).getCol());
                Point p1 = getInputPos(i, c);
                Point p2 = inp.c.getType().getOutputPos(inp.output, inp.c);
                g.drawLine(p1.x, p1.y, p2.x, p2.y);
            }
        }
    }

    /**
     * The default draw method
     * 
     * @param g
     *            the graphics context to draw on
     * @param selected
     *            true to highlight the image when it's the current focus
     */
    public void draw(Graphics g, boolean selected, Component c) {
        g.setColor(selected ? Color.GRAY : LIGHT_GREY);
        g.fillRect(c.rect.x, c.rect.y, c.rect.width, c.rect.height);

        g.setColor(selected ? Color.RED : Color.BLACK);
        g.drawRect(c.rect.x, c.rect.y, c.rect.width, c.rect.height);

        g.setColor(selected ? Color.WHITE : Color.BLACK);
        g.drawString(name, c.rect.x + 2, c.rect.y + 12);

        for (ConnectionInfo i : inputList)
            i.draw(g, c.rect.x, c.rect.y);
        for (ConnectionInfo i : outputList)
            i.draw(g, c.rect.x, c.rect.y);
    }
    
    /**
     * Does the magic of seeing where and how we might be intersecting with a
     * point
     * 
     * @param rect
     *            the rectangle for the component
     * @param p
     *            the point
     * @return data on the intersection, or null if none.
     * @TODO turn lists into arrays after layout
     */
    public ComponentAndConnection getComponentClick(Component c, Point p) {
        Point topLeft = c.rect.getLocation();

        // first scan inputs and outputs - woefully inefficient because these
        // are linked lists.

        for (int i = 0; i < inputList.size(); i++) {
            if (inputList.get(i).intersects(topLeft, p)) {
                return new ComponentAndConnection(c, ComponentClickType.INPUT,
                        i);
            }
        }
        for (int i = 0; i < outputList.size(); i++) {
            if (outputList.get(i).intersects(topLeft, p)) {
                return new ComponentAndConnection(c, ComponentClickType.OUTPUT,
                        i);
            }
        }

        // then just the rectangle
        if (c.rect.contains(p)) {
            return new ComponentAndConnection(c);
        } else {
            return null;
        }
    }
    
    // the parameter specifications are actually just parameters
    // which get cloned into the individual parameters for the actual
    // components. We do this by hacking with a memento!
    List<Parameter> parameterSpecs = new ArrayList<Parameter>();
    public void addParameter(Parameter p){
    	parameterSpecs.add(p);
    }

    public Parameter[] createParameters(Component component){
    	Parameter[] ps = new Parameter[parameterSpecs.size()];
    	for(int i=0;i<parameterSpecs.size();i++){
    		Parameter proto = parameterSpecs.get(i);
    		Parameter.Memento m = proto.createMemento();
    		ps[i]=m.create();
    	}
    	return ps;
    }

}
