package org.pale.stumpy.main;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import org.pale.stumpy.model.Patch;
import org.pale.stumpy.patchview.PatchView;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Menu;

/**
 * The file menu.
 * 
 * @author white
 * 
 */

@SuppressWarnings("serial")
public class FileMenu extends Menu {
    /**
     * Constructor, which adds the menu items.
     */
    public FileMenu(Controller ctr) {
        super("File",ctr);

        addMenuItem("New",KeyEvent.VK_N, "new");
        addMenuItem("Open", KeyEvent.VK_O, "open");
        addMenuItem("Save", KeyEvent.VK_S, "save");
        addMenuItem("Quit", KeyEvent.VK_W, "quit");
        
    }

}
