package org.pale.stumpy2.ui;

import java.util.LinkedList;
import java.util.List;

import org.pale.stumpy2.ui.support.ComponentCommandBindings;
import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.Refreshable;

import bibliothek.gui.dock.common.CControl;
import bibliothek.gui.dock.toolbar.location.CToolbarLocation;

/**
 * A toolbar in docking frames is not a component - the toolbar buttons are added
 * to the station for the toolbar in the main frame. This class gets a toolbar location
 * to add things to, however.
 * @author white
 *
 */
public class Toolbar implements Refreshable {
	/// this binds components to commands
	private ComponentCommandBindings bindings = new ComponentCommandBindings();
	/// location of toolbar
	private CToolbarLocation loc;
	/// the index of the next item to add
	private int addIdx=0;
	/// the Docking Frames control object
	private CControl control;
	private List<ToolbarButton> buttons = new LinkedList<ToolbarButton>();
	
	// takes the DockingFrams control object, the toolbar location, and 
	// the Controller which should field the commands.
	public Toolbar(CControl c,CToolbarLocation initLoc, Controller ctr){
		loc = initLoc;
		control = c;
		bindings.setController(ctr);
		Controller.addRefreshable(this);
	}
	
	static int idctr=0;
	public void add(String name, String iconname, String command){
		// we generate the ID from the name passed in: it has to be unique
		// across the entire system.
		ToolbarButton item = new ToolbarButton(name+(idctr++),name,iconname);
		buttons.add(item);
		item.setLocation(loc.item(addIdx++)); //add the item in the next slot.
		control.addDockable( item ); // and add it to the control
		item.addBindings(bindings,command); // make the bindings object respond
		item.setVisible( true );
	}
	
	public void destroy(){
		for(ToolbarButton item: buttons){
			control.removeDockable(item);
			item.setVisible(false);
			item.removeFromBindings(bindings);
		}
		buttons.clear();
		buttons = null;
		bindings = null;
		Controller.removeRefreshable(this);
	}

	@Override
	public void refresh() {
		bindings.refresh(); // redraw all the buttons?
	}

}
