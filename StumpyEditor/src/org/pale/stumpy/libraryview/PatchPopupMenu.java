package org.pale.stumpy.libraryview;

import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.PatchLibrary;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.PopupMenu;
import org.pale.stumpy.ui.Controller.Command;
import org.pale.stumpy.ui.Controller.CommandFactory;

/**
 * A menu for modifying the properties of patches within a patch library (such as which
 * is the active patch)
 * 
 * @author jaf18
 *
 */
class PatchPopupMenu extends PopupMenu {
	PatchPopupMenu(Controller c, final PatchLibrary lib, final Patch selected){
		super("",c);
		
		addMenuItem("set active",new CommandFactory() {
			
			@Override
			public Command create() {
				return new Command(false) {
					public void execute() {
						lib.setActivePatch(selected);
						
					}
				};
			}
		});
	}
}
