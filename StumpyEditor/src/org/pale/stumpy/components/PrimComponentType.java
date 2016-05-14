package org.pale.stumpy.components;

import java.util.ArrayList;
import java.util.List;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.paramtypes.EnumParam;

/**
 * This component draws primitives.
 * @author white
 *
 */
public class PrimComponentType extends ComponentType {
    List<String> primitiveNames = new ArrayList<String>();
    
    public PrimComponentType() {
        super("primitive","generator",70,70);
        
        addOutput(ConnectionType.get("flow"),"out");
        
        layout();
    }
    
    /// For this to work correctly we need a client connection to
    /// have been made, downloading the primitives.

    @Override
    public Parameter[] createParameters(Component component) {
    	String[] names;
    	if(primitiveNames.size() == 0)
    		names = new String[] { "???"};
    	else
    		names = primitiveNames.toArray(new String[primitiveNames.size()]);
    	
        return new Parameter[] {
                new EnumParam("prim", names,0)}; 
    }

	public void addPrimitiveName(String string) {
		// TODO Auto-generated method stub
		primitiveNames.add(string);
		
	}

}
