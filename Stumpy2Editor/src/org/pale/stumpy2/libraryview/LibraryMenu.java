package org.pale.stumpy2.libraryview;

import java.awt.event.KeyEvent;

import org.pale.stumpy2.ui.Menu;
import org.pale.stumpy2.ui.support.Controller;

@SuppressWarnings("serial")
public class LibraryMenu extends Menu {
	public LibraryMenu(Controller c) {
		super("Library", c);
		addMenuItem("New Patch",KeyEvent.VK_L,"newpatch");
		addMenuItem("Save Library",KeyEvent.VK_S,"save");
		addMenuItem("Copy Patch",KeyEvent.VK_C,"copy"); 
		addMenuItem("Cut Patch",KeyEvent.VK_X,"cut");
		addMenuItem("Sync Patch",KeyEvent.VK_Y,"sync");
		addMenuItem("Paste Patch",KeyEvent.VK_V,"paste");
		addMenuItem("Rename Patch","rename");
		addMenuItem("Delete Patch","delete");
	}			

}