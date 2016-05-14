package org.pale.stumpy.model;

import org.pale.stumpy.model.paramtypes.FloatParam;

/**
 * Base class for simple transform components which share common parameters and IO. It's not
 * in the actual component package because it's not a component, but a base class for components.
 * @author white
 *
 */
public class SimpleTransformComponentType extends ComponentType {
    
    protected SimpleTransformComponentType(String name){
        
        super(name,"transforms",70,70);
        
        addInput(ConnectionType.get("flow"),"in");
        addInput(ConnectionType.get("float"),"mod");
        
        addOutput(ConnectionType.get("flow"),"out");
        
        layout();

    }

    @Override
    public Parameter[] createParameters(Component component) {
        return new Parameter[] {
                new FloatParam("x",-100,100,0),      
                new FloatParam("y",-100,100,0),      
                new FloatParam("z",-100,100,0),      
                new FloatParam("modx",-10,10,0),      
                new FloatParam("mody",-10,10,0),      
                new FloatParam("modz",-10,10,0),      
              };
    }

}
