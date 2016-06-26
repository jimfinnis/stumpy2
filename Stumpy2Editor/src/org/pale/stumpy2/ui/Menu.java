package org.pale.stumpy2.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

import org.pale.stumpy2.ui.support.ComponentCommandBindings;
import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.UIElement;
import org.pale.stumpy2.ui.support.Controller.CommandFactory;
import org.pale.stumpy2.ui.support.Refreshable;

@SuppressWarnings("serial")
public class Menu extends JMenu implements Refreshable, MenuListener, ActionListener {
	

    ComponentCommandBindings bindings = new ComponentCommandBindings();

    /**
     * Constructor, which takes the name and passes it to the JMenu ctor.
     * 
     * @param name
     */
    public Menu(String name, Controller c) {
        super(name);
        bindings.setController(c);
        addMenuListener(this);
        addActionListener(this);
        Controller.addRefreshable(this);
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
    public void addMenuItem(String name, int ctrlKey, String command) {
    	MenuItemElement i = new MenuItemElement(name);
        i.setAccelerator(KeyStroke.getKeyStroke(ctrlKey,
                java.awt.Event.CTRL_MASK));
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, command);
    }

    /**
     * Add a menu item with a string binding and no shortcut
     * @param name
     * @param command
     */
    public void addMenuItem(String name, String command) {
    	MenuItemElement i = new MenuItemElement(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, command);
    }
    
    /**
     * Add a menu item without a shortcut, with a factory binding
     */
    public void addMenuItem(String name, CommandFactory f) {
    	MenuItemElement i = new MenuItemElement(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, f);
    }

    /**
     * Add a menu item with a shortcut key, with a factory binding.
     */	
    public void addMenuItem(String name, int ctrlKey, CommandFactory f) {
    	MenuItemElement i = new MenuItemElement(name);
        i.setAccelerator(KeyStroke.getKeyStroke(ctrlKey,
                java.awt.Event.CTRL_MASK));
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, f);
    }


    @Override
    public void refresh() {
        bindings.refresh();
    }

    @Override
    public void menuCanceled(MenuEvent e) {
    }

    @Override
    public void menuDeselected(MenuEvent e) {
    }

    @Override
    public void menuSelected(MenuEvent e) {
        refresh();
        System.out.println("Select");
    }

	@Override
	public void actionPerformed(ActionEvent e) {
		System.out.println("Action in menu");
	}

}
