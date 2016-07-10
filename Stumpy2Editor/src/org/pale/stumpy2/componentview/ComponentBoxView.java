package org.pale.stumpy2.componentview;

import java.awt.Container;
import java.awt.Dimension;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;

import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener;
import org.pale.stumpy2.ui.ControlledDockable;
import org.pale.stumpy2.ui.support.Images;

import bibliothek.gui.dock.common.CLocation;
import bibliothek.gui.dock.common.layout.RequestDimension;

/**
 * Displays a list of components and their editors.
 * @author white
 *
 */
public class ComponentBoxView extends ControlledDockable implements PatchChangeListener {
	private static ComponentBoxView instance;
	/// the components being displayed in the list, as a map to the component panels
	private Map<Component,ComponentPanel> map = new HashMap<Component,ComponentPanel>();
	private LinkedList<Component> list = new LinkedList<Component>();
	private Container pane;
	
	public static void createInstance(){
		instance = new ComponentBoxView();
	}
	
	public static ComponentBoxView getInstance(){
		return instance;
	}

	private ComponentBoxView() {
		super("compbox");
		setTitleIcon(Images.getImageIcon("icons/bricks"));
		pane = new JPanel();
		pane.setLayout(new BoxLayout(pane,BoxLayout.PAGE_AXIS));
		JScrollPane scpane = new JScrollPane(pane);
		scpane.setMinimumSize(new Dimension(300,200));
		getContentPane().add(scpane);
	}

	/**
	 * rebuild the list and pane contents, reusing components
	 * if they are already present.
	 */
	void regenerate(){
		// remove all components from the pane
		pane.removeAll();
		for(Component c: list){
			// for each component, if it has an entry in the map add the panel there back,
			// otherwise create a new panel and add it to the map.
			ComponentPanel p;
			if(map.containsKey(c))
				p = map.get(c);
			else {
				p = new ComponentPanel(c.getPatch(),c);
				map.put(c, p);
			}
			
			pane.add(p);
		}
		pane.revalidate();
		pane.repaint();
	}

	/**
	 * Add a component to the list. Will not recreate the panel
	 * if it's already there.
	 */
	public void add(Component c){
		if(list.contains(c))
			list.remove(c);
		list.addFirst(c);
		regenerate();
		map.get(c).reveal();
	}
	
	/**
	 * Remove a set of components from the pane.
	 */
	public void removeSet(Set<Component> s){
		boolean changed=false;
		for(Component c: s){
			System.out.println("Change is remove "+c.getType().getName());
			if(list.contains(c)){
				System.out.println("Component found; removing");
				list.remove(c);
				map.remove(c);
				changed=true;
			}
		}
		if(changed){
			regenerate();
		}
	}

	@Override
	public void onPatchChange(Patch p, PatchChange change) {
		System.out.println("Change received in compbox");
		switch(change.getType()){
		case REMOVESET:
			removeSet(change.getSet());
			break;
		default:break;
		}
	}

	public void setSelected(Component c, boolean b) {
		if(map.containsKey(c)){
			map.get(c).setSelected(b);
		}
	}

}
