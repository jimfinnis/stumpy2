package org.pale.stumpy.components;

import java.awt.Point;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.FloatParam;

public class OscComponent extends ComponentType {

    public OscComponent() {
        super("osc", "numeric",70,70);
        ConnectionType f = ConnectionType.get("float");
        addInput(f,"mod");
        addOutput(f,"out");
        
        layout();
    }

    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter [] {
                new FloatParam("freq",0,100,1),
                new FloatParam("mod",-5,5,0)
        };
    }

}
