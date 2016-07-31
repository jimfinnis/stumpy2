package org.pale.stumpy2.patchview;

import java.awt.event.KeyEvent;

import org.pale.stumpy2.ui.Menu;
import org.pale.stumpy2.ui.support.Controller;


public class PatchMenu extends Menu {

	public PatchMenu(Controller c) {
		super("Patch", c);
		addMenuItem("Copy",KeyEvent.VK_C,"copy");
		addMenuItem("Cut",KeyEvent.VK_X,"cut");
		addMenuItem("Paste",KeyEvent.VK_V,"paste");
	}

}
