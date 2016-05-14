package org.pale.stumpy.patchview.commands;

import java.util.Set;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.MementoizationException;
import org.pale.stumpy.patchview.PatchView;
import org.pale.stumpy.ui.Controller.Command;

public class CopyCommand extends Command {
    
    private PatchView pv;
    private Set<Component> set;

    public CopyCommand(PatchView pv){
        super(true);
        
        this.pv = pv;
        this.set = pv.getSelected();
    }

    @Override
    public void execute() throws MementoizationException {
        pv.copyToClipboard(set);

    }

}
