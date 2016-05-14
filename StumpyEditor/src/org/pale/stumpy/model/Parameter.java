package org.pale.stumpy.model;

import java.util.List;

import javax.swing.JComponent;
import javax.swing.JPanel;

public abstract class Parameter {
    
    private int id;
    
    public int getID(){
        return id;
    }
    
    /**
     * The memento. Must be a JavaBean. You should extend this in your parameter subclasses.
     * @author white
     *
     */
    static public abstract class Memento {
        public Memento(){}
        public String getName() {
            return name;
        }
        public void setName(String name) {
            this.name = name;
        }
        public String getEncodedValue() {
            return encodedValue;
        }
        public void setEncodedValue(String encodedValue) {
            this.encodedValue = encodedValue;
        }
        public void setID(int id) {
            this.id = id;
        }
        public int getID(){
            return id;
        }

        /**
         * Implement this - create a new Parameter from the memento
         */
        public abstract Parameter create();
        
        String name;
        String encodedValue;
        int id;
    }
    
    /**
     * Generate the memento - you should implement this, being sure to call setCoreMemento() on it
     */
    public abstract Memento createMemento();
    
    /**
     * Set the core values in a memento. Call this from all createMemento implementations
     */
    public void setCoreMemento(Memento m){
        m.setName(name);
        m.setID(id);
        m.setEncodedValue(getEncodedValue());
    }

    /**
     * The value of this parameter
     */
    private String encodedValue;

    /**
     * The name of the parameter
     */
    private String name;

    
    public Parameter(String name) {
        this.name = name;
    }

    /**
     * Get the name
     */
    public String getName(){
        return name;
    }
    
    /**
     * Get the parameter's value encoded as a string
     */
    public String getEncodedValue(){
        return encodedValue;
    }
    
    /** 
     * Set the value encoded as a string. Only the editor widgets should call this.
     */
    public void setEncodedValue(String s){
        encodedValue = s;
    }
    
    /**
     * This retrieves the special identifying character used to do typechecking, which must agree
     * with that given on the server side for the corresponding parameter in checkCode() calls.
     * 
     */

    public abstract char getCodeChar();
    
    /**
     * Create a new control which can edit this parameter
     * @param parameterChangeListener 
     * @return
     */
    abstract public JComponent createControl(ParameterChangeListener parameterChangeListener);
    
    /**
     * Write a command to send this parameter's value to the server
     * @param cmds the list of commands to add the command to
     * @param patchid the ID of the patch containing the component
     * @param componentid the ID of the component containing the param
     * @param paramidx  the index of the param within the component
     */
    public void writeSyncCommand(List<String> cmds, int patchid, int componentid) {
        cmds.add("p "+patchid+" "+componentid+" "+id+" "+getCodeChar()+" "+getEncodedValue());
    }

    /**
     * Set this parameter's ID within its component type. Called after createParameters() has been called.
     * @param i
     */
    public void setID(int i) {
        id = i;
    }
}
