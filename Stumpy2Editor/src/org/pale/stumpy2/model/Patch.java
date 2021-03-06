package org.pale.stumpy2.model;

import java.awt.Point;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import org.pale.stumpy2.model.PatchChangeListener.PatchChange;
import org.pale.stumpy2.model.PatchChangeListener.PatchChangeType;
import org.pale.stumpy2.patchview.PatchView;

import bibliothek.gui.dock.common.intern.CDockable;

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
	public PatchLibrary lib; // the lib I'm in
	
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
	private List<PatchView> views = new LinkedList<PatchView>();

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
	
	public Component getComponentByID(int id){
		for(Component c: components){
			if(c.id == id)
				return c;
		}
		return null;
	}

	/**
	 * Find a component which intersects the given position, and whether we were
	 * on an input or output. This runs through the list of items backwards,
	 * so that items at the end (drawn last) are scanned first.
	 * 
	 * @param p
	 *            a point on the canvas
	 * @param curpage 
	 * @return an object describing what's at the click, or null for no
	 *         component
	 */

	public ComponentAndConnection getComponentAtPoint(final Point p, int curpage) {
		Iterator<Component> ri = components.descendingIterator();
		while(ri.hasNext()){
			Component c = ri.next();
			ComponentAndConnection cc = c.getComponentClick(p,curpage);
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

	public Component addComponent(String name, Point pos, int curpage)
			throws UnknownComponentTypeException, NoCurrentPatchException {

		System.out.println("Trying to make "+name);

		ComponentType t = ComponentTypeRegistry.getInstance().getComponentType(
				name);
		Component c = t.create(this,pos,curpage);
		components.addLast(c);

		notifyChange(new PatchChangeListener.PatchChange(PatchChangeType.ADD, c));

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
		notifyChange(new PatchChangeListener.PatchChange(PatchChangeType.REMOVESET,
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
		notifyChange(new PatchChangeListener.PatchChange(
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
		notifyChange(new PatchChangeListener.PatchChange(PatchChangeType.UNLINKINPUT,
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
		notifyChange(new PatchChangeListener.PatchChange(PatchChangeType.NAME));
	}

	/**
	 * add a view to the view list
	 */
	public void addToViews(PatchView v) {
		views.add(v);
	}

	/**
	 * remove a view from the list of open views of this patch
	 */
	public void removeFromViews(PatchView v) {
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
		for (PatchView v : views) {
			// NO IDEA if this will work.
			v.close();
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
	public void notifyChange(PatchChangeListener.PatchChange change) {
		for (PatchChangeListener p : patchChangeListeners) {
			p.onPatchChange(this, change);

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
						} else {
							// if the input component index wasn't found - meaning that it is
							// outside the subset from which this memento was made - use the
							// raw index, but with a high bit set so we know it's an EXTERNAL
							// index (i.e. one from the set as a whole.
							int[] d = new int[2];
							d[0] = outCompIdx + 16384;
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
	 * @param isLoad this is a load of an entire patch, not a paste of a subset
	 * @throws UnknownComponentTypeException
	 * @throws ConnectionTypeMismatchException
	 * @throws ConnectionOutOfRangeException
	 */
	public Collection<Component> resetFromMemento(Memento m,boolean isLoad)
			throws UnknownComponentTypeException,
			ConnectionOutOfRangeException, ConnectionTypeMismatchException {

		// set the straightforward properties
		if(isLoad)
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
			Component c = new Component(cm,this);
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
				if (d != null){
					// if the output component index has 16384 set, that means
					// rather than being an index into the set of components in
					// the memento, it's an index into the patch itself. This is 
					// because it's a connection coming into a clipboard memento from
					// outside that memento's set. Capisce?
					Component out;
					if(d[0]>16383){
						out = components.get(d[0] & ~16384);
					} else {
						out = pairing[d[0]].c;
					}
					int outIndex = d[1];
					pairing[i].c.setInput(j, out, outIndex);
				}
			}
		}
		notifyChange(new PatchChangeListener.PatchChange(PatchChangeType.ADDSET,
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
		notifyChange(new PatchChange(PatchChangeType.LINK, c, input, c2, output));
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

    /**
     * rehash all components, reassociating them with types from the new typemap.
     * This could actually screw things up royally if the new type is really different.
     * @throws UnknownComponentTypeException 
     */
	public void rehash() throws UnknownComponentTypeException {
		for (Component c : components) {
			c.rehash();
		}
	}
}
