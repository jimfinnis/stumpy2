package org.pale.stumpy.model;

/**
 * Abstract class - make one to get informed when a parameter changes its value
 * @author white
 *
 */
public abstract class ParameterChangeListener {
    private Patch patch;
    private Component component;
    
    public ParameterChangeListener(Component c, Patch patch){
        this.patch = patch;
        this.component = c;
    }
    public Patch getPatch() {
        return patch;
    }
    public Component getComponent() {
        return component;
    }


    public abstract void onChange(Parameter p);
}
