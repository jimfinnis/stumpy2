package org.pale.stumpy2.ui;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

import org.pale.stumpy2.ui.support.ComponentCommandBindings;
import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.Controller.CommandFactory;
import org.pale.stumpy2.ui.support.Refreshable;
import org.pale.stumpy2.ui.support.UIElement;

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
    
    /// wrapper class because we need a subclass of UIElement
    class MenuItemElement extends JMenuItem implements UIElement {
		public MenuItemElement(String name) {
			super(name);
		}
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
        MenuItemElement i = new MenuItemElement(name);
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
        MenuItemElement i = new MenuItemElement(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, c);
    }
    
    @Override
    public void refresh() {
        bindings.refresh();
        
    }
}
