package org.pale.stumpy2.patchview.commands;

import java.util.Set;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.MementoizationException;
import org.pale.stumpy2.patchview.PatchView;

public class CopyCommand extends org.pale.stumpy2.ui.support.Controller.Command {
    
    private PatchView pv;
    private Set<Component> set;

    public CopyCommand(PatchView pv){
        super(true);
        
        this.pv = pv;
        //this.set = pv.getSelected();
    }

    @Override
    public void execute() throws MementoizationException {
        //pv.copyToClipboard(set);

    }

}
