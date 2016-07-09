package org.pale.stumpy2.patchview;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Set;

import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.border.BevelBorder;

import org.pale.stumpy2.Main;
import org.pale.stumpy2.componentview.ComponentBoxView;
import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.ConnectionOutOfRangeException;
import org.pale.stumpy2.model.ConnectionTypeMismatchException;
import org.pale.stumpy2.model.MementoizationException;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener;
import org.pale.stumpy2.model.UnknownComponentTypeException;
import org.pale.stumpy2.ui.ControlledDockable;
import org.pale.stumpy2.ui.support.Images;

import bibliothek.gui.dock.common.event.CDockableStateListener;
import bibliothek.gui.dock.common.event.CVetoClosingEvent;
import bibliothek.gui.dock.common.event.CVetoClosingListener;
import bibliothek.gui.dock.common.intern.CDockable;
import bibliothek.gui.dock.common.mode.ExtendedMode;

/**
 * @author white
 *
 */
public class PatchView extends ControlledDockable implements PatchChangeListener, CDockableStateListener {
	static int pvidx=0; // counter for ID generation
	/**
	 * The patch this view is viewing
	 */
	private Patch patch;

	/**
	 * The scroller we embed the canvas into
	 */
	private JScrollPane scroller;

	/**
	 * A status bar
	 */
	private JLabel statusBar;
	/**
	 * The canvas for editing.
	 */
	private PatchCanvas canvas;

	public Patch getPatch(){
		return patch;
	}
	
	public PatchView(Patch p) {
		super("pv"+(pvidx++));

		setController(PatchViewController.getInstance());
		PatchViewController.getInstance().setView(this);
		Main.getControl().addDockable(this);
		
		Container pane = getContentPane();
		setTitleIcon(Images.getImageIcon("icons/page"));
		
		canvas = new PatchCanvas(p,this);
		scroller = new JScrollPane(canvas);
		scroller.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		scroller.setPreferredSize(new Dimension(600,600));
		pane.add(scroller, BorderLayout.CENTER);

		// add a status bar

		statusBar = new JLabel();
		statusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));
		statusBar.setHorizontalAlignment(SwingConstants.LEFT);
		setStatus("ready");
		pane.add(statusBar,BorderLayout.SOUTH);

		patch = p;
		p.addPatchChangeListener(this);
		p.addPatchChangeListener(ComponentBoxView.getInstance());
		p.addToViews(this);
		setTitleText(p.toString());

		setCloseable(true);
		addCDockableStateListener(this);
		
		setFocusComponent(canvas);
		
		setVisible(true);
	}
    /**
     * 
     * @return the view's scroll pane, which wraps the editor canvas
     */
    public JScrollPane getScrollPane(){
        return scroller;
    }
    
    /**
     * Set the status text
     * @param t
     */
    public void setStatus(String t){
        statusBar.setText(t);
    }
    
    
    /**
     * 
     * @return true if both scrollbars are visible (so we can scroll out)
     */
    public boolean areScrollbarsVisible(){
        boolean h = scroller.getHorizontalScrollBar().isVisible();
        boolean v = scroller.getVerticalScrollBar().isVisible();
        return h && v;
    }
    
    /**
     * This important method deals with changes in the model.
     * 
     * @param change
     *            a set of changes
     */
    @Override
    public void update(Patch p,PatchChange change) {
        // if the patch changes its name, set our title.
    	switch(change.getType()){
    	case NAME:
            setTitleText(patch.getName());
            break;
    	case ADD:
    	case ADDSET:
    	case REMOVESET:
    	case UNLINKINPUT:
    	case UNLINKOUTPUT:
    	case LINK:
    		canvas.repaint();
    		break;
		default:
			break;
    	}
    }
    
	/**
	 * attempt to close the dockable
	 */
	public void close(){
		getAction(CDockable.ACTION_KEY_CLOSE).intern().trigger(intern().asDockable());	
	}



    Patch.Memento clipboard;

    /**
     * 
     * @param set the set I want to copy to the clipboard
     * @throws MementoizationException
     */
    public void copyToClipboard(Set<Component> set) throws MementoizationException {
       clipboard = patch.createMemento(set);
        
    }

    public void cutToClipboard(Set<Component> set) throws MementoizationException {
        clipboard = patch.createMemento(set);
        patch.removeSet(set);
        canvas.unselectAll();
    }

    /**
     * Paste the items from the clipboard, select them, then copy the new
     * items into the clipboard (in order that the add offset works!)
     * @throws UnknownComponentTypeException
     * @throws ConnectionOutOfRangeException
     * @throws ConnectionTypeMismatchException
     * @throws MementoizationException 
     */
    public void pasteFromClipboard() throws UnknownComponentTypeException, ConnectionOutOfRangeException, ConnectionTypeMismatchException, MementoizationException {
        Collection<Component> cs = patch.resetFromMemento(clipboard,false);
        
        canvas.unselectAll();
        for(Component c: cs){
        	c.rect.x += 10*canvas.scale;
        	c.rect.y += 10*canvas.scale;
        	canvas.select(c);
        }
        copyToClipboard(canvas.getSelected());
        
    }

    public Set<Component> getSelected() {
        return canvas.getSelected();
    }

	@Override
	public void extendedModeChanged(CDockable arg0, ExtendedMode m) {
	}

	@Override
	public void visibilityChanged(CDockable v) {
		if(!v.isVisible()){
			patch.removePatchChangeListener(this);
			patch.removePatchChangeListener(ComponentBoxView.getInstance());
			patch.removeFromViews(this);
			
			removeCDockableStateListener(this);
		}
	}


}
