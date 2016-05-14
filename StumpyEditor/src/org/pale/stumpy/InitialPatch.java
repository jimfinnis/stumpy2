package org.pale.stumpy;

import java.awt.Point;
import java.util.LinkedList;

import org.pale.stumpy.client.Client;
import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentTypeRegistry;
import org.pale.stumpy.model.NoCurrentPatchException;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.UnknownComponentTypeException;

/**
 * This is a class which extends patch, initialising it to create an initial basic patch to work with.
 * @author white
 *
 */
public class InitialPatch extends Patch {
    public InitialPatch(){
        Component c;
        
        try {
            addComponent("output",new Point(0,0));
            addComponent("test",new Point(200,220));
            
            LinkedList<String> cmds = new LinkedList<String>();
            writeSyncCommands(cmds);
            if(Client.isConnected())
                Client.getInstance().send(cmds);
            
            
        
        } catch (UnknownComponentTypeException e) {
            throw new RuntimeException("unknown type in initial patch: "+e.getTypeName());
        } catch (NoCurrentPatchException e) {
            throw new RuntimeException("no current patch in initial patch");
        }
    }
}
