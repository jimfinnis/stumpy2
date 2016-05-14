package org.pale.stumpy.ui;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

import javax.swing.JButton;
import javax.swing.JOptionPane;

import org.pale.stumpy.patchview.PatchCanvas;
import org.pale.stumpy.ui.Controller.CommandFactory;

/**
 * Handles a set of components and their associated command factories or strings
 * in association with a controller, so that they can be enabled/disabled
 * accordingly when the controller changes.
 * 
 * UGLY because we have to handle both types of command - those which are command factories,
 * and those which are strings bound to command factories inside the controller.
 * 
 * @author white
 * 
 */
public class ComponentCommandBindings implements ActionListener {

    /**
     * The controller - initially, it's null. It needs to be set before the
     * class will work.
     */
    private Controller controller;

    /**
     * Set the controller to which commands will be sent.
     * 
     * @param c
     */
    public void setController(Controller c) {
        controller = c;
        refresh();
    }

    /**
     * Handle an event being fed to a given component. Looks up the command and
     * runs it in the controller.
     * 
     * @param c
     * @throws Exception 
     */
    public void handle(Component c) throws Exception {
        if (null != controller) {
            CommandFactory cmd = map.get(c);
            if (null != cmd) {
                controller.handle(cmd.create());
            } else {
                String s = smap.get(c);
                if (null != s) {
                    controller.handle(s);
                }
            }
        }
    }

    /**
     * Set the enabled state of the given component according to whether it is
     * acceptable to the controller chain.
     * 
     * @param cmd
     *            the command factory
     */
    void setEnabled(Component c) {
        if (null != controller) {
            CommandFactory cmd = map.get(c);
            if (null != cmd) {
                c.setEnabled(cmd.enabled());
            } else {
                String s = smap.get(c);
                if (null != s) {
                    c.setEnabled(controller.acceptable(s));
                }
            }
        }
    }

    /**
     * A set of item/command pairs
     */
    Map<Component, CommandFactory> map = new HashMap<Component, CommandFactory>();
    /**
     * A set of item/command pairs (for shortcut commands linked into the
     * controller)
     */
    Map<Component, String> smap = new HashMap<Component, String>();

    /**
     * Add a component to the bindings, given the component and the command factory to
     * run on the controller when that component is actioned.
     * 
     * @param c
     * @param cmd
     */
    public void add(Component c, CommandFactory cmd) {
        map.put(c, cmd);
        setEnabled(c);
    }

    /**
     * Add a component to the bindings, given the component and the string command to
     * run on the controller when that component is actioned.
     * 
     * @param c
     * @param cmd
     */
    public void add(Component c, String cmd) {
        smap.put(c, cmd);
        setEnabled(c);
    }

    /**
     * Calling this will iterate over all the components and set their enabled
     * state to whether the controller will accept their associated command.
     */

    public void refresh() {
        for (Map.Entry<Component, CommandFactory> e : map.entrySet()) {
            setEnabled(e.getKey());
        }
        for (Map.Entry<Component, String> e : smap.entrySet()) {
            setEnabled(e.getKey());
        }
    }

    /**
     * Handle a command, given the component - just calls handle()
     */

    @Override
    public void actionPerformed(ActionEvent arg0) {
        try {
            handle((Component) arg0.getSource());
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null,
                    "CCB Error: " + e.getMessage());
        }

    }

    public Controller getController() {
        return controller;
    }

}
