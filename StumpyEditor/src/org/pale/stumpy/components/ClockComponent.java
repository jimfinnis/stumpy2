package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.FloatParam;

public class ClockComponent extends ComponentType {
    
    public ClockComponent(){
        super("clock","numeric",70,-1);
        addOutput(ConnectionType.get("float"), "out");
        
        layout();
    }

    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter[] {
                new FloatParam("mul",-100,100,1)
        };
    }

}
