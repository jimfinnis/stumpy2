package org.pale.stumpy.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.KeyStroke;

import org.pale.stumpy.ui.Controller.CommandFactory;

/**
 * A class connecting the popup menu with our controller/binding system, to make life
 * easier writing popups and tying them into controllers.
 * 
 * @author white
 *
 */
public class PopupMenu extends JPopupMenu implements Refreshable {
    
    ComponentCommandBindings bindings = new ComponentCommandBindings();
    
    /**
     * Used by extensions to get the controller
     * @return
     */
    public Controller getController(){
        return bindings.getController();
    }

    /**
     * Constructor, which takes the name and passes it to the JMenu ctor.
     * 
     * @param name
     */
    public PopupMenu(String name, Controller c) {
        super(name);
        bindings.setController(c);
    }

    /**
     * Method for adding a menu item with an command, takes the name of the
     * item, the shortcut key (which is pressed in association with CTRL) and
     * the controller which will handle the command.
     * 
     * @param name
     * @param ctrlKey
     * @param command
     */
    protected void addMenuItem(String name, String command) {
        JMenuItem i = new JMenuItem(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, command);
    }
    
    /**
     * Method for adding a menu item which uses a command factory
     * @param name
     * @param c
     */
    protected void addMenuItem(String name, CommandFactory c){
        JMenuItem i = new JMenuItem(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, c);
    }


    @Override
    public void refresh() {
        bindings.refresh();
        
    }
}
