package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.FloatParam;

public class MulComponent extends ComponentType {
    
    public MulComponent(){
        super("mul","numeric",70,-1);
        ConnectionType f = ConnectionType.get("float");
        addInput(f,"input 1");
        addInput(f,"input 2");
        layout();
    }

    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter [] {
                new FloatParam("add 1",-100,100,0),
                new FloatParam("mul 1",-100,100,1),
                new FloatParam("add 2",-100,100,0),
                new FloatParam("mul 2",-100,100,1),
        };
    }

}
