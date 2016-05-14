package org.pale.stumpy.patchview;

import javax.swing.JFrame;

import org.pale.stumpy.model.Patch;
import org.pale.stumpy.patchview.commands.CopyCommand;
import org.pale.stumpy.patchview.commands.CutCommand;
import org.pale.stumpy.patchview.commands.PasteCommand;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Controller.Command;

/**
 * This controller handles menu and toolbar commands for the patch view
 * @author white
 *
 */
public class PatchViewController extends Controller {
    private Patch patch;
    private PatchView pv;

    /**
     * Constructor
     * @param alertFrame the frame which is used to show alert messages
     * @param c the controller which is the next in the chain (unhandled messages go here)
     * @param p the patch we're controlling
     */
    public PatchViewController(final PatchView pv, Controller c, Patch p) {
        super(pv,c);

        patch = p;

        add("copy",new CommandFactory() {
            
            @Override
            public Command create() {
                return new CopyCommand(pv);
            }
        });

        add("cut",new CommandFactory() {
            
            @Override
            public Command create() {
                return new CutCommand(pv);
            }
        });

        add("paste",new CommandFactory() {
            
            @Override
            public Command create() {
                return new PasteCommand(pv);
            }
        });

    }
}
