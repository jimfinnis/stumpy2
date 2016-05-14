package org.pale.stumpy.patchview.commands;

import org.pale.stumpy.model.ConnectionOutOfRangeException;
import org.pale.stumpy.model.ConnectionTypeMismatchException;
import org.pale.stumpy.model.MementoizationException;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.patchview.PatchView;
import org.pale.stumpy.ui.Controller.Command;

public class PasteCommand extends Command {

    private PatchView pv;

    public PasteCommand(PatchView pv) {
        super(true);
        this.pv = pv;
    }

    @Override
    public void execute() throws UnknownComponentTypeException, ConnectionOutOfRangeException, ConnectionTypeMismatchException, MementoizationException {
        this.pv.pasteFromClipboard();
    }

    @Override
    public void undo(){
        
    }
}
