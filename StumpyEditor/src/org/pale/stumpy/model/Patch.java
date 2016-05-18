package org.pale.stumpy.model;

import java.util.List;
import java.awt.Point;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.Collection;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;

import javax.swing.JFrame;

import org.pale.stumpy.model.PatchChangeListener.PatchChange;
import org.pale.stumpy.model.PatchChangeListener.PatchChangeType;

/**
 * A patch is a directed graph of Components. Each patch is a "template" for a
 * patch instance; many instances of the same patch may be running on the same
 * server via macros. Therefore, patches and their components do not contain any
 * instance data - just parameter data which, if changed in one patch, change in
 * all the running patch instances.
 * 
 * @author white
 * 
 */
public class Patch {
	/** counter used to construct unique IDs */
	static int idcounter;
	/**
	 * Unique (for all patches) id used by server
	 */
	int id;

	/**
	 * Our list of components (it's a list because there's an implicit
	 * ordering for selection.)
	 */
	private LinkedList<Component> components = new LinkedList<Component>();

	/**
	 * The name of the patch; initially untitled
	 */
	private String name = "untitled";

	/**
	 * A set of items listening for patch changes. Add with
	 * addPatchChangeListener(). Remove with removePatchChangeListener().
	 * 
	 */
	private Set<PatchChangeListener> patchChangeListeners = new HashSet<PatchChangeListener>();

	/**
	 * list of open views. We can't do anything with them apart from get rid of
	 * them!
	 */
	private List<JFrame> views = new LinkedList<JFrame>();

	/**
	 * Constructor for creating a patch from a memento
	 * 
	 * @param pm
	 * @throws ConnectionTypeMismatchException
	 * @throws ConnectionOutOfRangeException
	 * @throws UnknownComponentTypeException
	 */
	public Patch(Memento pm) throws UnknownComponentTypeException,
	ConnectionOutOfRangeException, ConnectionTypeMismatchException {
		this();
		resetFromMemento(pm,true);
	}

	/**
	 * Default constructor for an empty patch; also sets the ID
	 */
	public Patch() {
		id = idcounter++;
	}

	/**
	 * Run a visitor over my innards
	 * 
	 * @param v
	 *            a Visitor object to perform an operation over each component
	 */
	public void visitAll(Visitor v) {
		for (Component c : components) {
			c.accept(v);
		}
	}

	/**
	 * Return the ID of the patch within the library
	 */
	public int getID(){
		return id;
	}

	/**
	 * Find a component which intersects the given position, and whether we were
	 * on an input or output. This runs through the list of items backwards,
	 * so that items at the end (drawn last) are scanned first.
	 * 
	 * @param p
	 *            a point on the canvas
	 * @return an object describing what's at the click, or null for no
	 *         component
	 */

	public ComponentAndConnection getComponentAtPoint(final Point p) {
		Iterator<Component> ri = components.descendingIterator();
		while(ri.hasNext()){
			Component c = ri.next();
			ComponentAndConnection cc = c.getComponentClick(p);
			if (null != cc)
				return cc;
		}
		return null;
	}

	/**
	 * add a component by name, returning the new component. Adds the component
	 * to the start of the list.
	 * 
	 * @param name
	 *            the name of the component type
	 * @param pos
	 *            the position of the new component in the editor canvas
	 * @return the new component
	 * @throws UnknownComponentTypeException
	 * @throws NoCurrentPatchException
	 */

	public Component addComponent(String name, Point pos)
			throws UnknownComponentTypeException, NoCurrentPatchException {

		System.out.println("Trying to make "+name);

		ComponentType t = ComponentTypeRegistry.getInstance().getComponentType(
				name);
		Component c = t.create(pos);
		components.addLast(c);

		update(new PatchChangeListener.PatchChange(PatchChangeType.ADD, c));

		return c;
	}

	/**
	 * Bring the given component to the front of the list, so it will
	 * be drawn last and selected first.
	 * @param c
	 */
	public void toFront(Component c){
		components.remove(c);
		components.addLast(c);
	}

	/**
	 * Remove a component from the collection, deleting any links it may have to
	 * other components. If you want to remove components yourself, call
	 * removeSet() instead.
	 * 
	 * @param c
	 */
	private void remove(final Component c) {
		components.remove(c);

		visitAll(new Visitor() {
			@Override
			public void visitComponent(Component p) {
				p.removeInputConnections(c, -1);
			}
		});
	}

	/**
	 * Remove a set of components
	 * 
	 * @param selected
	 */

	public void removeSet(Set<Component> set) {
		for (Component c : set) {
			remove(c);
		}
		update(new PatchChangeListener.PatchChange(PatchChangeType.REMOVESET,
				set));

	}

	/**
	 * Unlink an output connection. Finds all matching inputs and unlinks them.
	 * 
	 * @param c
	 *            the component
	 * @param output
	 *            the output index
	 */
	public void unlinkOutput(final Component c, final int output) {
		visitAll(new Visitor() {
			@Override
			public void visitComponent(Component p) {
				p.removeInputConnections(c, output);
			}
		});
		update(new PatchChangeListener.PatchChange(
				PatchChangeType.UNLINKOUTPUT, c, 0, null, output));
	}

	/**
	 * Unlink an input connection.
	 * 
	 * @param c
	 * @param input
	 * @throws ConnectionOutOfRangeException
	 */
	public void unlinkInput(Component c, int input)
			throws ConnectionOutOfRangeException {
		c.unsetInput(input);
		update(new PatchChangeListener.PatchChange(PatchChangeType.UNLINKINPUT,
				c, input));
	}

	/**
	 * Get the patch name
	 * 
	 * @return the patch name
	 */
	public String getName() {
		return name;
	}

	/**
	 * return the patch name
	 */
	public String toString() {
		return getName();
	}

	/**
	 * Set the patch name an notify all listeners. Will clear the copyNumber.
	 * 
	 * @param name
	 */
	public void setName(String name) {
		this.name = name;
		update(new PatchChangeListener.PatchChange(PatchChangeType.NAME));
	}

	/**
	 * add a view to the view list
	 */
	public void addToViews(JFrame v) {
		views.add(v);
	}

	/**
	 * remove a view from the list of open views of this patch
	 */
	public void removeFromViews(JFrame v) {
		views.remove(v);
	}

	/**
	 * 
	 * @return true if the patch has open views
	 */
	public boolean hasOpenViews() {
		return views.size() > 0;
	}

	/**
	 * Close all open views of this patch
	 */
	public void closeAllViews() {
		for (JFrame v : views) {
			v.dispose();
		}
	}

	/**
	 * add a new patch change listener
	 * 
	 * @param p
	 */
	public void addPatchChangeListener(PatchChangeListener p) {
		patchChangeListeners.add(p);
	}

	/**
	 * Remove a listener from the list of patch change listeners.
	 * 
	 * @param p
	 */
	public void removePatchChangeListener(PatchChangeListener p) {
		patchChangeListeners.remove(p);
	}

	/**
	 * Send a message to all PatchChangeListeners. The type of the change is an
	 * EnumSet.
	 * 
	 * @param change
	 *            the change which has occurred
	 */
	public void update(PatchChangeListener.PatchChange change) {
		for (PatchChangeListener p : patchChangeListeners) {
			p.update(this, change);

		}
	}

	/**
	 * create a memento object
	 * 
	 * @param subset
	 *            if not null, only use this subset to create the memento,
	 *            otherwise use the entire patch.
	 * @return
	 * @throws MementoizationException
	 */
	public Memento createMemento(Set<Component> subset)
			throws MementoizationException {
		Memento m = new Memento();
		List<Component.Memento> componentList = new LinkedList<Component.Memento>();

		// we need to build a map which maps from component number in the patch
		// to component number in the subset, so we can wire things correctly
		// when we're only copying part of the patch.

		HashMap<Integer,Integer> mapFromPatchToSubsetIdx = new HashMap<Integer,Integer>();

		int ct=0;
		for (Component c : components) {
			if(subset == null || subset.contains(c))
				mapFromPatchToSubsetIdx.put(getComponentIndex(c), ct++);
		}


		for (Component c : components) {
			if (subset == null || subset.contains(c)) {
				// create the basics
				Component.Memento cm = c.createMemento();

				// create the input wiring data
				int inct = c.getType().getInputCount();
				int[][] inputData = new int[inct][]; // an array of pairs of
				// ints describes the
				// inputs
				for (int i = 0; i < inct; i++) {
					Component.Input inp = c.getInput(i);
					if (inp != null) {
						int outCompIdx = getComponentIndex(inp.c);
						// if the output we want this input connected to
						// is in our subset (which could be the whole patch)
						// add it to to the input data with the index in the subset
						// we worked out and stored in our map.
						if(mapFromPatchToSubsetIdx.containsKey(outCompIdx)){
							int[] d = new int[2]; // data about each input is stored
							// in the memento as 2 ints:
							// (component index, output index)
							d[0] = mapFromPatchToSubsetIdx.get(outCompIdx);
							d[1] = inp.output;
							inputData[i] = d;
						}
					}
				}
				cm.setInputData(inputData); // and write to the memento for the
				// component

				componentList.add(cm);
			}
		}
		m.setComponentList(componentList);
		m.setName(name);
		return m;
	}

	/**
	 * Adds components to a patch from a memento - used in both cut/paste and
	 * loading. Returns a collection of the new components (which is used to add
	 * a positional offset in cut/paste)
	 * 
	 * @param m
	 * @throws UnknownComponentTypeException
	 * @throws ConnectionTypeMismatchException
	 * @throws ConnectionOutOfRangeException
	 */
	public Collection<Component> resetFromMemento(Memento m,boolean setName)
			throws UnknownComponentTypeException,
			ConnectionOutOfRangeException, ConnectionTypeMismatchException {

		// set the straightforward properties
		setName(m.getName());

		// useful class for associating mementoes with their components
		class Pairing {
			public Pairing(Component.Memento cm, Component c2) {
				m = cm;
				c = c2;
			}

			Component.Memento m;
			Component c;
		}
		Pairing[] pairing = new Pairing[m.componentList.size()];

		// this is for notification purposes
		Set<Component> notification = new HashSet<Component>();

		// first pass - create the components
		int i = 0;
		for (Component.Memento cm : m.getComponentList()) {
			Component c = new Component(cm);
			components.addLast(c); // append to end
			notification.add(c);
			pairing[i] = new Pairing(cm, c);
			i++;
		}

		// now wire them up

		for (i = 0; i < pairing.length; i++) {
			Component.Memento cm = pairing[i].m;

			int inputData[][] = cm.getInputData();
			for (int j = 0; j < inputData.length; j++) {
				int d[] = inputData[j];
				if (d != null) {
					Component out = pairing[d[0]].c;
					int outIndex = d[1];
					pairing[i].c.setInput(j, out, outIndex);
				}
			}
		}
		update(new PatchChangeListener.PatchChange(PatchChangeType.ADDSET,
				notification));
		return notification;

	}

	/**
	 * Return the index of a given component within the component list
	 * 
	 * @param c
	 * @return
	 * @throws MementoizationException
	 */

	private int getComponentIndex(Component c) throws MementoizationException {
		int cs = components.size();
		int i = 0;
		for (Component cInList : components) {
			if (cInList == c)
				return i;
			i++;
		}
		throw new MementoizationException("could not find index of component");
	}

	/**
	 * The memento class
	 */
	public static class Memento {
		String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		List<Component.Memento> componentList;

		public List<Component.Memento> getComponentList() {
			return componentList;
		}

		public void setComponentList(List<Component.Memento> componentList) {
			this.componentList = componentList;
		}
	}

	/**
	 * Link the input of one component to the output of another. Will also use
	 * update() to notify listeners of the change.
	 * 
	 * @param c
	 *            the component whose input we want to link
	 * @param input
	 *            the index of the input
	 * @param c2
	 *            the component to which we want to link
	 * @param output
	 *            the index of the output in c2
	 * @throws ConnectionOutOfRangeException
	 * @throws ConnectionTypeMismatchException
	 */

	public void setComponentInput(Component c, int input, Component c2,
			int output) throws ConnectionOutOfRangeException,
			ConnectionTypeMismatchException {
		c.setInput(input, c2, output);
		update(new PatchChange(PatchChangeType.LINK, c, input, c2, output));
	}

	/**
	 * Append synchronisation commands
	 * 
	 * @param cmds
	 */
	public void writeSyncCommands(List<String> cmds) {
		cmds.add("np " + id);

		// first, output the components themselves
		for (Component c : components) {
			c.writeSyncCreateCommands(cmds, id);
		}
		// then write the linkages and parameters
		for (Component c : components) {
			c.writeSyncLinkCommands(cmds, id);
			c.writeSyncParamCommands(cmds, id);
		}
		synced=true;
	}

	/// indicates that the patch has been uploaded to the server, so
	/// change commands should be sent there.
	private boolean synced=false;

	public boolean isSynced(){
		return synced;
	}

	/**
	 * Append a command to instantiate this patch - to actually start running it
	 * as the primary patch
	 * 
	 * @param cmds
	 */

	public void writeInstantiateCommand(List<String> cmds) {
		cmds.add("run " + id);

	}
}
