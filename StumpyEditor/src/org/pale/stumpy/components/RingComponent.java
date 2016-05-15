package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.FloatParam;
import org.pale.stumpy.model.paramtypes.IntParam;

public class RingComponent extends ComponentType {

	public RingComponent() {
		super("ring", "complex", 70, -1);
		addInput(ConnectionType.get("flow"),"in");
		addInput(ConnectionType.get("float"),"mod");
		addOutput(ConnectionType.get("flow"),"out");
		layout();
	}
    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter [] {
                new IntParam("count",2,100,4),
                new FloatParam("radius",0,100,1),
                new FloatParam("scale",0,10,1),
                new FloatParam("radmod",-10,10,0),
                new FloatParam("scalemod",-10,10,0)
        };
    }

}
