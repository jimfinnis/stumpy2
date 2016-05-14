package org.pale.stumpy.libraryview;

import java.awt.event.KeyEvent;

import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Menu;

public class EditMenu extends Menu {

    public EditMenu(Controller c) {
        super("Edit", c);
        
        addMenuItem("Cut",KeyEvent.VK_X,"cut");
        addMenuItem("Copy",KeyEvent.VK_C,"copy");
        addMenuItem("Paste",KeyEvent.VK_V,"paste");
        addSeparator();
        addMenuItem("Sync","sync");
    }
}
