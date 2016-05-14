/**
 * 
 */
package org.pale.stumpy.libraryview;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.AbstractListModel;
import javax.swing.DefaultListModel;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;
import javax.swing.ListModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import org.pale.stumpy.main.FileMenu;
import org.pale.stumpy.main.TopController;
import org.pale.stumpy.model.MementoizationException;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.PatchLibrary;
import org.pale.stumpy.patchview.PatchView;
import org.pale.stumpy.patchview.PatchViewPopup;
import org.pale.stumpy.ui.PopupMenu;
import org.pale.stumpy.ui.Refreshable;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.ToolbarFrame;
import org.w3c.dom.views.AbstractView;

/**
 * A view of a patch library
 * 
 * @author white
 * 
 */
public class PatchLibraryView extends ToolbarFrame implements Refreshable {

    /**
     * The library we are viewing
     */
    private PatchLibrary library;

    public String getFileName() {
        return library.getFileName();
    }

    /**
     * A view of the stuff
     */
    private JList list;
    
    /**
     * This renders each patch entry
     * @author jaf18
     *
     */
    class MyCellRenderer extends JLabel implements ListCellRenderer{

    	public MyCellRenderer(){
    		setOpaque(true);
    	}
    	
		@Override
		public Component getListCellRendererComponent(
				JList list, Object value, int index,
				boolean isSelected, boolean cellHasFocus) {
		    Patch p = (Patch)value;
			String s = p.getName() + " ";
			setText(s);
			
			Color bg,fg;
			
			
			if(isSelected){
				bg = list.getSelectionBackground();
				fg = list.getSelectionForeground();				
			} else {
				bg = list.getBackground();
				fg = list.getForeground();				
			}
			
			if(library.getActivePatch()==p)
				fg = new Color(255,0,0);

			setBackground(bg);
			setForeground(fg);
			return this;
		}
    	
    }

    /**
     * The abstract list model which wraps the list data. This needs to be
     * informed when things changed so the list can be redrawn.
     */
    class MyListModel extends AbstractListModel implements
            PatchLibrary.ChangeListener {

        @Override
        public Patch getElementAt(int index) {
            return library.getPatchList().get(index);
        }

        @Override
        public int getSize() {
            return library.getPatchList().size();
        }

        @Override
        public void onAddItem() {
            fireIntervalAdded(this, getSize() - 1, getSize() - 1);
        }

        @Override
        public void onChangeItem(int n) {
            fireContentsChanged(this, n, n);

        }

        @Override
        public void onRemoveItem(int n) {
            fireIntervalRemoved(this, n, n);
        }
    }

    /**
     * Remove the selected patch, if there is a selection.
     * 
     * @return true if there was a selection.
     */
    public boolean removeSelectedPatch() {
        int idx = list.getSelectedIndex();
        if (idx < 0)
            return false;
        Patch p = library.getPatchList().get(idx);
        library.removePatch(p);
        return true;
    }

    /**
     * return the selected patch
     * 
     * @return
     */
    public Patch getSelectedPatch() {
        int idx = list.getSelectedIndex();
        if (idx < 0)
            return null;
        Patch p = library.getPatchList().get(idx);
        return p;
    }

    private MyListModel model;

    /**
     * Construct a new patch library view
     * 
     * @param p
     *            the library
     */
    public PatchLibraryView(PatchLibrary p) {
        library = p;

        // set the controller - the top controller is the next thing in the
        // chain of responsibility.
        setController(new PatchLibraryViewController(this,
                TopController.getInstance(), p));

        model = new MyListModel();
        library.addChangeListener(model);
        setTitle(getFileName());
        
        list = new JList(model);
        list.setCellRenderer(new MyCellRenderer());
        
        list.addKeyListener(new KeyListener() {

            @Override
            public void keyTyped(KeyEvent arg0) {
            }

            @Override
            public void keyReleased(KeyEvent arg0) {
            }

            @Override
            public void keyPressed(KeyEvent arg0) {
                try {
                switch (arg0.getKeyCode()) {
                case KeyEvent.VK_DELETE:
                    getController().handle("delete");
                    break;
                case KeyEvent.VK_F2:
                    getController().handle("rename");
                    break;
                }
                } catch(Exception e) {
                    JOptionPane.showMessageDialog(PatchLibraryView.this, "PV Error: "+e.getMessage());
                }
            }
        });
        list.addMouseListener(new MouseListener() {
            private void handlePopup(MouseEvent e){
            	if(e.isPopupTrigger() && getSelectedPatch()!=null){
            		PopupMenu m = new PatchPopupMenu(getController(), library, getSelectedPatch());
            		m.show(list,e.getX(),e.getY());
            	}
            }

            @Override
            public void mouseReleased(MouseEvent arg0) {
            	handlePopup(arg0);
            }

            @Override
            public void mousePressed(MouseEvent arg0) {
            	handlePopup(arg0);
            }

            @Override
            public void mouseExited(MouseEvent arg0) {
            }

            @Override
            public void mouseEntered(MouseEvent arg0) {
            }

            // on a double click, open a patch view
            @Override
            public void mouseClicked(MouseEvent arg0) {
                int idx = list.getSelectedIndex();
                if (arg0.getButton()==MouseEvent.BUTTON1 && arg0.getClickCount() == 2) {
                    Patch p = library.getPatchList().get(idx);
                    new PatchView(p);
                } 
            }
        });
        
        list.addListSelectionListener(new ListSelectionListener(){
            @Override
            public void valueChanged(ListSelectionEvent arg0) {
                refresh();
            }
        });

        setMinimumSize(new Dimension(200, 500));

        getContentPane().add(new JScrollPane(list));
        pack();
        setVisible(true);

        addWindowListener(new WindowListener() {
            @Override
            public void windowActivated(WindowEvent arg0) {
                TopController.getInstance().setCurrentLibrary(library);
            }

            @Override
            public void windowClosed(WindowEvent arg0) {
                TopController.getInstance().setCurrentLibrary(null);
                library.removeChangeListener(model);
            }

            @Override
            public void windowClosing(WindowEvent arg0) {
            }

            @Override
            public void windowDeactivated(WindowEvent arg0) {
            }

            @Override
            public void windowDeiconified(WindowEvent arg0) {
            }

            @Override
            public void windowIconified(WindowEvent arg0) {
            }

            @Override
            public void windowOpened(WindowEvent arg0) {
            }
        });
        
        createToolBar();
        createMenuBar();

    }


    /**
     * Add items to the toolbar
     * 
     */
    private void createToolBar() {
        addButton("toolbarButtonGraphics/general/New16", "Create a new patch",
                "New", "new");
        addButton("toolbarButtonGraphics/general/Copy16", "Copy a patch",
                "Copy", "copy");
        addButton("toolbarButtonGraphics/general/Cut16", "Cut a patch", "Cut",
                "cut");
        addButton("toolbarButtonGraphics/general/Paste16", "Paste a patch",
                "Paste", "paste");
        addButton("toolbarButtonGraphics/general/Export16", "Sync to server","Sync","sync");
        
    }

    /**
     * add menus to the menu bar
     */
    private void createMenuBar() {
        addMenu(new FileMenu(getController()));
        addMenu(new EditMenu(getController()));
    }

    public Patch.Memento getMementoForSelectedPatch()
            throws MementoizationException {
        int idx = list.getSelectedIndex();
        if (idx >= 0) {
            Patch p = library.getPatchList().get(idx);
            return p.createMemento(null);
        } else
            return null;
    }
}
