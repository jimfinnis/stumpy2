package org.pale.stumpy2.patchview.commands;

import org.pale.stumpy2.model.ConnectionOutOfRangeException;
import org.pale.stumpy2.model.ConnectionTypeMismatchException;
import org.pale.stumpy2.model.MementoizationException;
import org.pale.stumpy2.model.UnknownComponentTypeException;
import org.pale.stumpy2.patchview.PatchView;

public class PasteCommand extends org.pale.stumpy2.ui.support.Controller.Command {

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
