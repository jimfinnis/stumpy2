package org.pale.stumpy.ui;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.pale.stumpy.model.PatchLibrary;
import org.pale.stumpy.patchview.commands.DeleteCommand;

/**
 * This is a controller. It takes commands, and either handles them or not.
 * If the command is unhandled, it is passed on to the fallback controller if that has been set. Otherwise
 * the command remains unhandled.
 * 
 * The controller actually maps strings onto CommandFactory objects. This makes it easy to write controllers
 * which accept string commands, which can be linked to menu or toolbar objects without messy boilerplate. For example,
 * you might write a controller which maps "new" onto a command factory which generates a command to create new patches.
 * Then, you can write a toolbar with a button which produces the "new" command, and a menu item which does the same.
 * Linking these both to the same factory will produce a 
 * 
 * Commands are added by adding ControllerCommands to a Map<String,ControllerCommand> - this means that we can check the map
 * for whether a command is acceptable. You'll probably do this in the constructor.
 * 
 * @author white
 *
 */
public class Controller {
    
    /**
     * Controller commands are implementations of this, usually anon inner. These are factory objects - they
     * produce a Command when their create method is called. This contains all the necessary information to
     * perform the command, and calling execute() on it will do the business. 
     * @author white
     *
     */
    public static abstract class CommandFactory {
        /** produces a Command object containing the necessary information. Running this
         * will actually do the command. 
         * @return */
        public abstract Command create();
        /** true if the command would do anything (returning false here "greys out" a menu item etc.) */
        public boolean enabled(){
            return true;
        }
    }
    
    /**
     * The interface for commands.
     */
    public abstract static class Command {
        private boolean done;
        private boolean undoable;
        
        
        /**
         * constructor
         * @param undoable
         */
        public Command(boolean undoable){
            this.undoable = undoable;
        }

        /** actually run the command. Must do the following:
         * - run the command
         * - store any undo information
         * - mark the command as done 
         * @throws Exception 
         */
        public abstract void execute() throws Exception;
        
        /**
         * Mark the command has having been executed
         */
        public void markDone(){
            done = true;
        }
        
        /**
         * Has the command been executed?
         */
        public boolean isDone(){
            return done;
        }
        
        /**
         * Is the command undoable?
         */
        public boolean isUndoable(){
            return undoable;
        }
        
        /** undo the command - override this and set undoable to true in your ctor (and check that done is true!) */
        public void undo() {
            
        }
        
    }
    
    /**
     * Constructor
     * @param alertFrame the frame which should be used as a parent of dialogs
     * @param fallback the next controller in the chain of responsibility, which should handle any commands I don't understand. May be null.
     */
    public Controller(JFrame alertFrame, Controller fallback){
        this.alertFrame = alertFrame;
        this.fallback=fallback;
    }
    
    /**
     * Default constructor
     */
    public Controller(JFrame f){
        this(f,null);
    }
    
    /**
     * A frame to show alerts from
     */
    private JFrame alertFrame;
    
    /**
     * A list of things we should send refresh message to, once we've done something. This is static;
     * all controllers send refresh notifications to all views.
     */
    static List<Refreshable> refreshList = new LinkedList<Refreshable>();
    
    /**
     * A add to the list of refreshables
     */
    public static void addRefreshable(Refreshable c){
        refreshList.add(c);
    }
    
    /**
     * Remove from the list of refreshables
     */
    public static void removeRefreshable(Refreshable c){
        refreshList.remove(c);
    }
    
    /**
     * Notify that something may have changed
     */
    public static void notifyRefreshables(){
        for(Refreshable c: refreshList){
            c.refresh();
        }
    }

    
    
    /**
     * show an error - most exceptions should be dealt with this way!
     */
    public void showError(String s){
        JOptionPane.showMessageDialog(alertFrame, s);
    }


    /**
     * A map of command names to commands - the action to be performed when that command is received
     */
    private Map<String,CommandFactory> map = new HashMap<String,CommandFactory>();
    
    /**
     * The controller which should handle any commands we don't understand, or null if there
     * is no fallback.
     */
    private Controller fallback;


    /**
     * Handle a command - this is what's called by handle(String), but it may be called directly
     * too in the case of commands which have arguments, where we can't use a simple string mapping.
     * 
     * @TODO Undo processing will probably go in here.
     * @TODO also exception handling
     * @param c
     * @throws Exception 
     */
    public void handle(Command c) throws Exception {
        c.execute();
        notifyRefreshables();
    }
    
    /**
     * Handle a command if it exists in the map, or pass it on to the fallback. Used for shortcut
     * commands which have no arguments, which the controller can parse directly.
     * 
     * @param command
     * @return whether the command was ever handled.
     * @throws Exception 
     */
    public boolean handle(String command) throws Exception{
        boolean rv;
        CommandFactory r = map.get(command);
        
        if(null==r || !r.enabled()){
            if(null!=fallback){
                rv = fallback.handle(command);
            } else {
                rv = false;
            }
        } else {
            // create and execute the command
            handle(r.create());
            rv = true;
        }
        return rv;
    }
    
    
    
    /**
     * Does this command exist in the current controller or anywhere down the fallback chain? And if so, can it run?
     * @param command 
     * @return true if the command is acceptable, ie. it will actually run something.
     */
    
    public boolean acceptable(String command){
        boolean rv;
        CommandFactory r = map.get(command);
        
        if(null==r || !r.enabled()){
            if(null!=fallback){
                rv = fallback.acceptable(command);
            } else {
                rv = false;
            }
        } else {
            rv = true;
        }
        return rv;
    }
    
    /**
     * Add a command to the controller - you'll typically do this in a ctor.
     * @param command
     * @param r
     */
    public void add(String command,CommandFactory r){
        map.put(command,r);
    }

}
