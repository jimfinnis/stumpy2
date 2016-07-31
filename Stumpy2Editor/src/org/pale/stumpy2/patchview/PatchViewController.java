package org.pale.stumpy2.patchview;

import org.pale.stumpy2.TopController;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.patchview.commands.CopyCommand;
import org.pale.stumpy2.patchview.commands.CutCommand;
import org.pale.stumpy2.patchview.commands.PasteCommand;
import org.pale.stumpy2.ui.support.Controller;

/**
 * This controller handles menu and toolbar commands for the patch view
 * @author white
 *
 */
public class PatchViewController extends Controller {
    private static PatchViewController instance;
	private Patch patch;
    private PatchView view;
    
    public static void createInstance(){
    	instance = new PatchViewController(TopController.getInstance());
    }
    
    public static PatchViewController getInstance(){
    	return instance;
    }
    
    public void setView(PatchView v){
    	view = v;
    	patch = v.getPatch();
    }
    
    abstract class CommandFactoryCheckPatch extends CommandFactory {
    	@Override
    	public boolean enabled(){
    		return view != null;
    	}
    }
    abstract class CommandFactoryCheckPatchHasSelection extends CommandFactory {
    	@Override
    	public boolean enabled(){
    		return view != null;
    	}
    }
    abstract class CommandFactoryCheckPatchHasClip extends CommandFactory {
    	@Override
    	public boolean enabled(){
    		return view != null;
    	}
    }

    /**
     * Constructor
     * @param alertFrame the frame which is used to show alert messages
     * @param c the controller which is the next in the chain (unhandled messages go here)
     * @param p the patch we're controlling
     */
    private PatchViewController(Controller fallback) {
        super("patchview",null,fallback);


        add("copy",new CommandFactoryCheckPatchHasSelection() {
            
            @Override
            public Command create() {
                return new CopyCommand(view);
            }
        });

        add("cut",new CommandFactory() {
            
            @Override
            public Command create() {
                return new CutCommand(view);
            }
        });

        add("paste",new CommandFactory() {
            
            @Override
            public Command create() {
                return new PasteCommand(view);
            }
            @Override
            public boolean enabled(){
            	return view!=null && view.hasClipboard();
            }
            

        });

    }
}
