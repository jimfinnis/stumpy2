package org.pale.stumpy.patchview.commands;

import java.util.Set;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.ui.Controller.Command;

public class DeleteCommand extends Command {

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
