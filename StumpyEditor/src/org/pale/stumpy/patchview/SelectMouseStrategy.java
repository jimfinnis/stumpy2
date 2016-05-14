package org.pale.stumpy.patchview;

import java.awt.Point;
import java.awt.event.MouseEvent;

import org.pale.stumpy.model.ComponentAndConnection;
import org.pale.stumpy.model.Patch;

/**
 * A strategy for dealing with mouse events - this is the default strategy,
 * which moves components around, connects and disconnects patch connections.
 * 
 * @author white
 * 
 */
public class SelectMouseStrategy extends MouseStrategy {
    /**
     * Constructor
     * 
     * @param c
     *            the canvas we are editing with
     */
    public SelectMouseStrategy(PatchCanvas c) {
        super(c);
    }

    @Override
    public void mousePressed(MouseEvent e, Point ep) {
        if(handlePopUp(e,ep))return;
//        if(e.getButton()!=MouseEvent.BUTTON1)return;

        Patch p = canvas.getPatch();
        
        
        ComponentAndConnection cc = p.getComponentAtPoint(ep);
        if (cc != null) {
            switch (cc.type) {
            case NO_CONNECTION:
                // the "drag" case. Start dragging item or set.
                canvas.startDragComponent(cc.c, ep);
                break;
            case INPUT:
                canvas.breakConnection(cc);
            case OUTPUT:
                canvas.startConnectionRubberband(cc);
                canvas.handleConnectionRubberband(ep); // to initialise the endpoint
                break;
            }
            // handle double-clicks
            if(e.getClickCount() >= 2){
                canvas.openComponentView(cc.c);
            }
            
        } else {
            // not on a component, so start rubberbanding a selection box
            canvas.startDragSelection(ep);
        }
    }
    
    // we have to check for pop up triggers in both mousePressed() and mouseReleased(),
    // so I do it here.
    private boolean handlePopUp(MouseEvent arg0, Point ep){
        if(arg0.isPopupTrigger()) {
            canvas.openPopup(arg0, ep);
            return true;
        }
        return false;
    }


    @Override
    public void mouseReleased(MouseEvent e,Point ep) {
        if(handlePopUp(e,ep))return;
        if(e.getButton()!=MouseEvent.BUTTON1)return;
        if (canvas.isDraggingComponent())
            canvas.endDragComponent();
        if(canvas.isDraggingSelection())
            canvas.endDraggingSelection();
        if(canvas.isRubberbandingConnection())
            canvas.endConnectionRubberband(ep);
    }

    @Override
    public void mouseDragged(MouseEvent e, Point ep) {
        if (canvas.isDraggingComponent())
            canvas.handleDragComponent(ep);
        if(canvas.isDraggingSelection())
            canvas.handleDragSelection(ep);
        if(canvas.isRubberbandingConnection())
            canvas.handleConnectionRubberband(ep);
    }

}
