package org.pale.stumpy.patchview;

import java.awt.Point;
import java.awt.event.MouseEvent;

import javax.swing.event.MouseInputListener;

import org.pale.stumpy.model.Patch;

/**
 * A class which describes a strategy of dealing with mouse events to edit a patch. We
 * switch which strategy we use depending on the tool selected or the mode of the editor.
 * 
 * By default, events do nothing at all.
 * @author white
 *
 */
public class MouseStrategy {
    
    /**
     * The canvas being edited with
     */
    PatchCanvas canvas;

    /**
     * Constructor
     * @param patch
     */
    public MouseStrategy(PatchCanvas c) {
        this.canvas = c;
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseClicked(MouseEvent e, Point p) {
        
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseEntered(MouseEvent e, Point p) {
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseExited(MouseEvent e, Point p) {
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mousePressed(MouseEvent e, Point p) {
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseReleased(MouseEvent e, Point p) {
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseDragged(MouseEvent e, Point p) {
    }

    /**
     * Handle the appropriate mouse event. By default, does nothing.
     * @param e the original event
     * @param p the point within the event, transformed by the canvas' inverse transform
     */
    public void mouseMoved(MouseEvent e, Point p) {
    }

}
