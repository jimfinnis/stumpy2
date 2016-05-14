package org.pale.stumpy.ui;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;

import org.pale.stumpy.ui.Controller.CommandFactory;


/**
 * A handy menu class which makes it easier to add new menu items.
 * 
 * @author white
 * 
 */
@SuppressWarnings("serial")
public class Menu extends JMenu implements Refreshable, MenuListener {

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
        JMenuItem i = new JMenuItem(name);
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
        JMenuItem i = new JMenuItem(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, command);
    }
    
    /**
     * Add a menu item without a shortcut, with a factory binding
     */
    public void addMenuItem(String name, CommandFactory f) {
        JMenuItem i = new JMenuItem(name);
        i.addActionListener(bindings);
        add(i);
        bindings.add(i, f);
    }

    /**
     * Add a menu item with a shortcut key, with a factory binding.
     */
    public void addMenuItem(String name, int ctrlKey, CommandFactory f) {
        JMenuItem i = new JMenuItem(name);
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
    }

}
