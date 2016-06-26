package org.pale.stumpy2.patchview.commands;

import java.util.Set;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Patch;

public class DeleteCommand extends org.pale.stumpy2.ui.support.Controller.Command {

    private Set<Component> selected;
    private Patch patch;

    public DeleteCommand(Patch patch, Set<Component> selected) {
        super(false);
        this.patch = patch;
        this.selected = selected;
    }

    public void execute() {
        patch.removeSet(selected);
        
    }

}
