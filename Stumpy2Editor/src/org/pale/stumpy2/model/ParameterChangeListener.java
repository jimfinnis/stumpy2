package org.pale.stumpy2.model;

/**
 * Abstract class - make one to get informed when a parameter changes its value
 * @author white
 *
 */
public abstract class ParameterChangeListener {
    private Component component;
    
    public ParameterChangeListener(Component c){
        this.component = c;
    }
    public Patch getPatch() {
        return component.getPatch();
    }
    public Component getComponent() {
        return component;
    }


    public abstract void onChange(Parameter p);
}
