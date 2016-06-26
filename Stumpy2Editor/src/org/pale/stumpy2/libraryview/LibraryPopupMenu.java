package org.pale.stumpy2.libraryview;

import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchLibrary;
import org.pale.stumpy2.ui.PopupMenu;
import org.pale.stumpy2.ui.support.Controller;

public class LibraryPopupMenu extends PopupMenu {

	LibraryPopupMenu(Controller c, final PatchLibrary lib, final Patch selected){
		super("",c);
		
		addMenuItem("set active","setactive");
	}
}
