package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.paramtypes.IntParam;

/**
 * The Output component type.
 * @author white
 *
 */
public class OutputComponentType extends ComponentType {
    
    public OutputComponentType(){
        super("output","control",200,100); // call the superclass with appropriate data

        ConnectionType flow = ConnectionType.get("flow");
        
        addInput(flow,"input 0");
        addInput(flow,"input 1");
        addInput(flow,"input 2");
        addInput(flow,"input 3");
        
        layout();
    }

    @Override
    public Parameter[] createParameters(Component component) {
        return null;
    }
}
