package org.pale.stumpy;

import java.awt.Color;
import java.io.IOException;

import org.pale.stumpy.components.MoveComponentType;
import org.pale.stumpy.components.OutputComponentType;
import org.pale.stumpy.components.PrimComponentType;
import org.pale.stumpy.components.RotateComponentType;
import org.pale.stumpy.components.ScaleComponentType;
import org.pale.stumpy.components.TestComponentType;
import org.pale.stumpy.model.ComponentTypeRegistry;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.paramtypes.IntParam;

/**
 * This class contains static methods setting up the configuration, typically
 * creating new value and component types.
 * @author white
 *
 */
public class Configuration {

    public static void initialise() {
        
        // create the value types
        ConnectionType.create("flow", Color.BLACK);
        ConnectionType.create("float", Color.BLUE);
        
        ComponentTypeRegistry r = ComponentTypeRegistry.getInstance();
        try {
            r.autoRegister();
        } catch (Exception e) {
            System.out.println("Component autoregistration failed: "+e.getMessage());
            System.exit(1);
        }
        
/*        
        ComponentTypeRegistry r = ComponentTypeRegistry.getInstance();
        r.add(new OutputComponentType());
        r.add(new TestComponentType());
        r.add(new PrimComponentType());
        r.add(new MoveComponentType());
        r.add(new ScaleComponentType());
        r.add(new RotateComponentType());
        */
    }
}
