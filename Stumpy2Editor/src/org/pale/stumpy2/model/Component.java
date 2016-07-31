package org.pale.stumpy2.model;

import java.awt.Color;
import java.awt.Graphics;
import java.util.List;
import java.awt.Point;
import java.awt.Rectangle;
import java.sql.Connection;
import java.util.LinkedList;

import javax.swing.JComponent;
import javax.swing.JPanel;

import org.pale.stumpy2.componentview.ComponentBoxView;

/**
 * There are many possible components in a patch, and they're represented by
 * this class. This is the component in the patch, NOT the component instances
 * in the patch instance (but then the editor has no concept of instances, so
 * disregard that statement!)
 * 
 * @author white
 * 
 */
public class Component implements Visitable {
	/** counter used to construct unique IDs */
	static int idcounter;
	/** unique ID used by server */
	int id;

	/**
	 * The type of this component
	 */
	private ComponentType type;

	/**
	 * Position in canvas
	 */
	public Rectangle rect;

	/**
	 * Special text which may be sent from the server
	 */
	public String extraText;

	/**
	 * The connection (component and output) to which each input is connected.
	 * May be null.
	 */
	private Input[] inputs;

	/**
	 * The components parameters. This is created by the type's
	 * createParameters() method
	 */
	private Parameter[] params = null;

	/**
	 * A connection between two components - it's a link from an input of this
	 * component to an output of another
	 * 
	 * @author white
	 * 
	 */
	public class Input {
		Component c;
		int output;

		Input(Component c, int output) {
			this.c = c;
			this.output = output;
		}
	}

	// / array indicating whether getting a particular output always
	// / runs the component, or whether the cached version is used if it
	// / has been run before in this frame
	boolean[] runOutputAlways;
	private Patch patch;
	private String comment;

	public void setRunOutputAlways(int index, boolean state) {
		runOutputAlways[index] = state;
	}

	public void setComment(String c) {
		comment = c;
		ComponentBoxView.getInstance().commentChanged(this);
	}

	public String getComment(){
		return comment;
	}

	/**
	 * return the connection to this input.
	 * 
	 * @param i
	 */
	public Input getInput(int i) {
		return inputs[i];
	}

	/**
	 * @return component type
	 */
	public ComponentType getType() {
		return type;
	}

	/**
	 * create and set component type. Constructor is not public; it's only
	 * created by a factory method in the ComponentType.
	 * 
	 * @param type
	 * @param pos
	 *            position in canvas
	 */
	Component(Patch patch, ComponentType type, Point pos) {
		this.patch = patch;
		this.id = idcounter++;
		this.type = type;
		this.inputs = new Input[type.getInputCount()];
		this.runOutputAlways = new boolean[type.getOutputCount()];
		this.rect = new Rectangle(pos, type.getSize());
		this.params = type.createParameters(this);
		if (this.params == null) {
			// if that returned null, we'd still better create a zero-length
			// array
			this.params = new Parameter[0];
		}

		// run through the array and set the parameter IDs
		for (int i = 0; i < this.params.length; i++) {
			this.params[i].setID(i);
		}
	}

	/**
	 * Accept a visit from some visitor object - just passes it down.
	 */
	@Override
	public void accept(Visitor v) {
		v.visitComponent(this);
	}

	/**
	 * Set an input link to another component. DON'T call directly; use
	 * Patch.setComponentInput()
	 * 
	 * @param input
	 *            the input to connect in this component
	 * @param c
	 *            the component to which to connect
	 * @param output
	 *            the output of that component to which our input is connected
	 * @throws ConnectionOutOfRangeException
	 * @throws ConnectionTypeMismatchException
	 * 
	 */

	void setInput(int input, Component c, int output)
			throws ConnectionOutOfRangeException,
			ConnectionTypeMismatchException {
		if (input >= type.getInputCount())
			throw new ConnectionOutOfRangeException();
		if (output >= c.type.getOutputCount())
			throw new ConnectionOutOfRangeException();

		if(getType().getInputType(input).getID()<25 && 
				c.getType().getOutputType(output).getID()<25){ // type ID code 25 not checked (is ANY type).
			if (c.getType().getOutputType(output).getID() != getType()
					.getInputType(input).getID())
				throw new ConnectionTypeMismatchException();
		}

		inputs[input] = new Input(c, output);
	}

	/**
	 * Clear an input link from another component
	 * 
	 * @param input
	 *            index
	 * @throws ConnectionOutOfRangeException
	 */
	void unsetInput(int input) throws ConnectionOutOfRangeException {
		if (input >= type.getInputCount())
			throw new ConnectionOutOfRangeException();
		inputs[input] = null;
	}

	/**
	 * Remove any input connections to a given other component, or an input
	 * connect from a given output. Iterates through input array finding
	 * connections to the given component, setting them to null.
	 * 
	 * @param c
	 *            the component to remove
	 * @param j
	 *            the optional index of a particular output to remove, or -1 for
	 *            any output to that component
	 */
	public void removeInputConnections(Component c, int j) {
		for (int i = 0; i < this.inputs.length; i++) {
			if (inputs[i] != null && inputs[i].c == c
					&& (inputs[i].output == j || j == -1)) {
				inputs[i] = null;
			}
		}
	}

	/**
	 * Delegate drawing to the type object - done as two calls, so that we can
	 * override them separately
	 * 
	 * @throws ConnectionOutOfRangeException
	 *             this really shouldn't happen.
	 */
	public void draw(Graphics g, boolean highlight) {
		g.setColor(Color.BLACK);
		type.draw(g, highlight, this);
	}

	public void drawConnections(Graphics g, boolean highlight)
			throws ConnectionOutOfRangeException {
		type.drawConnections(g, highlight, this);
	}

	/**
	 * Create a list of editor widgets for the parameters of this component. We
	 * provide the patch so that the system an inform listeners of parameter
	 * changes.
	 * 
	 * @param parameterChangeListener
	 * @return a list of new JComponent
	 */
	public List<JComponent> createEditors(
			ParameterChangeListener parameterChangeListener) {
		List<JComponent> list = new LinkedList<JComponent>();
		if (params != null) {
			for (Parameter p : params) {
				JComponent e = p.createControl(parameterChangeListener);
				list.add(e);
			}
		}
		return list;
	}

	/**
	 * Is a click at the given point in this component, and if so, is it on an
	 * input or output?
	 * 
	 * @param p
	 *            the point on the canvas
	 * @return an object describing the component and input or output, or null.
	 */
	public ComponentAndConnection getComponentClick(Point p) {
		// first we check that it can intersect at all!
		Rectangle br = new Rectangle(rect);
		br.grow(ComponentType.CONNECTION_DETECT_WIDTH,
				ComponentType.CONNECTION_DETECT_WIDTH);

		// if that's true, go on to check all the inputs and outputs; a more
		// detailed check.
		if (br.contains(p)) {
			return type.getComponentClick(this, p);
		} else {
			return null;
		}
	}

	/**
	 * Component memento class - has to be a Bean, old bean, because we're using
	 * XMLEncoder
	 * 
	 * @author white
	 * 
	 */
	static public class Memento {
		/**
		 * The type of the component
		 */
		public String type;
		/**
		 * Its location on screen
		 */
		public Point location;

		/**
		 * The comment text
		 */
		public String comment;

		public String getComment() {
			return comment;
		}

		public void setComment(String comment) {
			this.comment = comment;
		}

		/**
		 * Connection data - an array of pairs of ints, with nulls instead of
		 * pairs where inputs are not connected. In each pair, 0=the index of
		 * the output component within the patch, 1=the index of that
		 * component's output
		 */
		int[][] inputData;
		boolean[] runOutputAlways;

		public boolean[] getRunOutputAlways() {
			return runOutputAlways;
		}

		public void setRunOutputAlways(boolean[] runOutputAlways) {
			this.runOutputAlways = runOutputAlways;
		}

		public int[][] getInputData() {
			return inputData;
		}

		public void setInputData(int[][] inputData) {
			this.inputData = inputData;
		}

		/**
		 * The parameters and their values
		 */
		public Parameter.Memento parameters[];

		public Parameter.Memento[] getParameters() {
			return parameters;
		}

		public void setParameters(Parameter.Memento[] parameters) {
			this.parameters = parameters;
		}

		public void setLocation(Point location) {
			this.location = location;
		}

		public Point getLocation() {
			return location;
		}

		public String getType() {
			return type;
		}

		public void setType(String type) {
			this.type = type;
		}

	}

	/**
	 * This creates a memento for all component data except the
	 * interconnections, which are managed by the patch memento
	 * 
	 * @return the memento, which needs interconnection data adding to it
	 */
	Memento createMemento() {
		Memento m = new Memento();
		m.setType(getType().getName());
		m.setLocation(new Point(rect.x, rect.y));
		m.setRunOutputAlways(runOutputAlways);
		m.setComment(comment);

		Parameter.Memento p[] = new Parameter.Memento[params.length];
		for (int i = 0; i < params.length; i++) {
			p[i] = params[i].createMemento();
		}
		m.setParameters(p);

		return m;
	}

	/**
	 * Create a components (sans connections) from a memento
	 * 
	 * @param cm
	 *            the memento
	 * @param patch
	 *            the patch to which I belong
	 * @throws UnknownComponentTypeException
	 */
	public Component(Memento cm, Patch patch)
			throws UnknownComponentTypeException {
		this.id = idcounter++;
		this.patch = patch;
		this.type = ComponentTypeRegistry.getInstance().getComponentType(
				cm.getType());
		Point pos = cm.getLocation();
		this.inputs = new Input[type.getInputCount()];
		this.rect = new Rectangle(pos, type.getSize());
		this.runOutputAlways = cm.getRunOutputAlways();
		this.comment = cm.getComment();
		// create the parameters from the parameter mementoes
		Parameter.Memento[] pms = cm.getParameters();
		params = new Parameter[pms.length];

		for (int i = 0; i < pms.length; i++) {
			params[i] = pms[i].create();
		}
	}

	/**
	 * Append to a list a command to create the component
	 * 
	 * @param cmds
	 * @param patchid
	 */
	public void writeSyncCreateCommands(List<String> cmds, int patchid) {
		cmds.add("nc " + patchid + " " + id + " " + type.getName());
		for (int i = 0; i < type.getOutputCount(); i++) {
			writeSyncRunAlwaysCommands(cmds, patchid, i);
		}
		// and commands to initialise the parameters
		writeSyncParamCommands(cmds, patchid);

	}

	/**
	 * Append a command to update the runalways state of an output
	 */
	public void writeSyncRunAlwaysCommands(List<String> cmds, int patchid,
			int output) {
		cmds.add("sra " + patchid + " " + id + " " + output + " "
				+ (runOutputAlways[output] ? "y" : "n"));

	}

	/**
	 * Append commands to link this component's inputs to others. Done as part
	 * of a complete sync, will not delete existing links etc.
	 * 
	 * @param cmds
	 * @param patchid
	 */
	public void writeSyncLinkCommands(List<String> cmds, int patchid) {
		for (int i = 0; i < type.getInputCount(); i++) {
			Input inp = inputs[i];
			if (inp != null)
				cmds.add("lc " + patchid + " " + id + " " + i + " " + inp.c.id
						+ " " + inp.output);
		}
	}

	/**
	 * Append commands to set all this component's parameters.
	 * 
	 * @param cmds
	 * @param patchid
	 */
	public void writeSyncParamCommands(List<String> cmds, int patchid) {
		if (params != null) {
			for (Parameter p : params) {
				p.writeSyncCommand(cmds, patchid, id);
			}
		}
	}

	/**
	 * Return the ID of the component within the patch
	 * 
	 * @return
	 */
	public int getID() {
		return id;
	}

	/**
	 * return the patch I'm in
	 * 
	 * @return
	 */
	public Patch getPatch() {
		return patch;
	}

	public void setExtraText(String str) {
		extraText = str;
	}

	/**
	 * set a new component type from the old one, getting the new one from the
	 * current list. If this new type has different params/connections this
	 * might be "fun".
	 * 
	 * @throws UnknownComponentTypeException
	 */

	public void rehash() throws UnknownComponentTypeException {
		String name = type.getName();
		type = ComponentTypeRegistry.getInstance().getComponentType(name);
	}

}
