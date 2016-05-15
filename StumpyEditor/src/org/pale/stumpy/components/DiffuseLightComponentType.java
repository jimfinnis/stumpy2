package org.pale.stumpy.components;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.BoolParam;
import org.pale.stumpy.model.paramtypes.FloatParam;
import org.pale.stumpy.model.paramtypes.IntParam;

public class DiffuseLightComponentType extends ComponentType {

    public DiffuseLightComponentType(){
        super("diffuse","lighting",150,-1); // call the superclass with appropriate data

        addInput(ConnectionType.get("flow"),"flow");
        addInput(ConnectionType.get("float"),"modulation");
        addOutput(ConnectionType.get("flow"), "flow");
        
        layout();
    }
    
    @Override
    public Parameter[] createParameters(Component component) {
        
        return new Parameter [] {
                new IntParam("light", 0, 3, 0),
                new FloatParam("red",0,1,0),
                new FloatParam("green",0,1,0),
                new FloatParam("blue",0,1,0),
                new FloatParam("red mod",-1,1,0),
                new FloatParam("green mod",-1,1,0),
                new FloatParam("blue mod",-1,1,0),
                new BoolParam("stack", false)
        };
    }

}
