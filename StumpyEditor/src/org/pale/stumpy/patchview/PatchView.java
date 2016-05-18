package org.pale.stumpy.patchview;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.net.URL;
import java.util.Collection;
import java.util.EnumSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;
import javax.swing.SwingConstants;
import javax.swing.border.BevelBorder;
import javax.swing.border.EmptyBorder;

import org.pale.stumpy.libraryview.EditMenu;
import org.pale.stumpy.main.Driver;
import org.pale.stumpy.main.FileMenu;
import org.pale.stumpy.main.TopController;
import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ConnectionOutOfRangeException;
import org.pale.stumpy.model.ConnectionTypeMismatchException;
import org.pale.stumpy.model.MementoizationException;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.PatchChangeListener;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.patchview.PatchCanvas.PatchKeyListener;
import org.pale.stumpy.ui.Refreshable;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.ToolbarFrame;

public class PatchView extends ToolbarFrame implements PatchChangeListener, WindowListener {

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

    /**
     * Create the frame.
     */
    public PatchView(Patch p) {
        // set the controller - the top controller is the next thing in the chain of responsibility.
        Controller c = new PatchViewController(this,TopController.getInstance(),p); 
        setController(c);
        createToolBar();
        createMenuBar();

        // create the actual editor pane inside a scrolling pane
        
        Container pane = getContentPane();
        
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
        p.addToViews(this);
        setTitle(p.toString());
        
        addWindowListener(this);

        
        pack();
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
     * Add items to the toolbar
     * 
     */
    private void createToolBar() {
        addButton("toolbarButtonGraphics/general/New16", "Create a new patch", "New", "new");
    }
    
    /**
     * add menus to the menu bar
     */
    private void createMenuBar(){
        
        addMenu(new FileMenu(getController()));
        addMenu(new EditMenu(getController()));
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
            setTitle(patch.getName());
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

    @Override
    public void windowActivated(WindowEvent e) {
        // here, we make sure the canvas has the keyboard focus when it is activated.
        canvas.requestFocusInWindow();
    }

    @Override
    public void windowClosed(WindowEvent e) {
    }

    @Override
    public void windowClosing(WindowEvent e) {
        patch.removePatchChangeListener(this);
        patch.removeFromViews(this);
    }

    @Override
    public void windowDeactivated(WindowEvent e) {
    }

    @Override
    public void windowDeiconified(WindowEvent e) {
    }

    @Override
    public void windowIconified(WindowEvent e) {
    }

    @Override
    public void windowOpened(WindowEvent e) {
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
}
