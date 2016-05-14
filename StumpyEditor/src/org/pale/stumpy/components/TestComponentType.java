package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.paramtypes.FloatParam;
import org.pale.stumpy.model.paramtypes.IntParam;

public class TestComponentType extends ComponentType {

    public TestComponentType() {
        super("test", "control",100, 100);
        
        ConnectionType flow = ConnectionType.get("flow");
        addInput(flow,"input 1");
        addInput(flow,"input 2");
        addInput(ConnectionType.get("float"),"input 3");
        
        addOutput(flow,"output 1");
        addOutput(flow,"output 2");
        addOutput(ConnectionType.get("float"),"output 3");
        
        layout();
    }
    
    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter[] {
                new IntParam("test",0,10,5),
                new FloatParam("float",0,10,4.5)
        };
        
    }
    
    

}
