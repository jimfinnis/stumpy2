package org.pale.stumpy2.ui;

import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.Refreshable;

import bibliothek.gui.dock.common.DefaultSingleCDockable;
import bibliothek.gui.dock.common.event.CFocusListener;
import bibliothek.gui.dock.common.intern.CDockable;

public class ControlledDockable extends DefaultSingleCDockable  {
	public ControlledDockable(String title){
		super(title);
		// we change which controller should get commands when we change focus
		addFocusListener(new CFocusListener() {
			@Override
			public void focusLost(CDockable arg0) {
			}
			
			@Override
			public void focusGained(CDockable arg0) {
				if(arg0 instanceof ControlledDockable){
					focused = ControlledDockable.this;
				}
			}
		});
	}
	
	protected void setController(Controller c){
		controller = c;
	}

	private Controller controller;
	static private ControlledDockable focused=null;
	public Controller getController(){
		return controller;
	}
	// get the controller which should get commands
	public static ControlledDockable getFocusedController(){
		return focused;
	}
}
