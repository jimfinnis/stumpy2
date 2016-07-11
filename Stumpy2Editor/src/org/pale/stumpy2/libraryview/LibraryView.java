package org.pale.stumpy2.libraryview;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.AbstractListModel;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.KeyStroke;
import javax.swing.ListCellRenderer;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import org.pale.stumpy2.Main;
import org.pale.stumpy2.componentview.ComponentBoxView;
import org.pale.stumpy2.model.MementoizationException;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchLibrary;
import org.pale.stumpy2.patchview.PatchView;
import org.pale.stumpy2.ui.ControlledDockable;
import org.pale.stumpy2.ui.PopupMenu;
import org.pale.stumpy2.ui.support.Images;

import bibliothek.gui.dock.common.CLocation;
import bibliothek.gui.dock.common.event.CDockableStateListener;
import bibliothek.gui.dock.common.event.CVetoClosingEvent;
import bibliothek.gui.dock.common.event.CVetoClosingListener;
import bibliothek.gui.dock.common.intern.CDockable;
import bibliothek.gui.dock.common.layout.RequestDimension;
import bibliothek.gui.dock.common.mode.ExtendedMode;

public class LibraryView extends ControlledDockable {
	private PatchLibrary library; // the library we are viewing
	private JList list; // list of the patches

	// render each cell
	class LibCellRenderer extends JLabel implements ListCellRenderer {

		LibCellRenderer(){
			setOpaque(true);
		}

		@Override
		public Component getListCellRendererComponent(JList list, Object value,
				int index, boolean isSelected, boolean hasFocus) {
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
			if(library==null)
				return 0;
			else
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

	public LibraryView(PatchLibrary p){
		super("patchlib"+p.getFileName());
		library = p;
		setLocation(CLocation.base().normalNorth(0.3));
		model = new MyListModel();
		library.addChangeListener(model);
		setTitleText(library.getFileName());
		setTitleIcon(Images.getImageIcon("icons/package"));
		setResizeRequest(new RequestDimension(200,true),true); // request width 200, not working

		list = new JList(model);
		list.setCellRenderer(new LibCellRenderer());
		LibraryViewController.getInstance().setView(this);

		setController(LibraryViewController.getInstance());

		// some very smelly code to stop the JList intercepting our keys, which should be handled
		// by the menu accelerators.
		list.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_C,java.awt.Event.CTRL_MASK), "none");
		list.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_X,java.awt.Event.CTRL_MASK), "none");
		list.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_V,java.awt.Event.CTRL_MASK), "none");
		
		list.addMouseListener(new MouseListener() {
			private void handlePopup(MouseEvent e){
				if(e.isPopupTrigger() && getSelectedPatch()!=null){
					PopupMenu m = new LibraryPopupMenu(getController(), library, getSelectedPatch());
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
					if(idx<library.getPatchList().size()){
						Patch p = library.getPatchList().get(idx);
						new PatchView(p);
					}
				} 
			}
		});

		list.addListSelectionListener(new ListSelectionListener(){
			@Override
			public void valueChanged(ListSelectionEvent arg0) {
				list.invalidate();
				LibraryViewController.getInstance().setView(LibraryView.this);
				LibraryViewController.notifyRefreshables();
			}
		});


		JScrollPane scpane = new JScrollPane(list);
		list.addFocusListener(new FocusListener(){
			@Override
			public void focusGained(FocusEvent arg0) {
				LibraryViewController.getInstance().setView(LibraryView.this);
				LibraryViewController.notifyRefreshables();
			}

			@Override
			public void focusLost(FocusEvent arg0) {
			}
		});
		scpane.setMinimumSize(new Dimension(200,100));
		add(scpane);
		// make sure we can close the library, and also that when we do
		// all the patches go away, and that the top controller loses access.
		// And that we refresh.
		setCloseable(true);
		addCDockableStateListener(new CDockableStateListener() {
			@Override
			public void visibilityChanged(CDockable arg0) {
				if(!arg0.isVisible()){
					LibraryViewController.getInstance().setView(null);
					library=null;
				}
			}
			@Override
			public void extendedModeChanged(CDockable arg0, ExtendedMode arg1) {}
		});
		
		
		addVetoClosingListener(new CVetoClosingListener() {
			
			@Override
			public void closing(CVetoClosingEvent arg0) {
				for(Patch p: library.getPatchList()){
					if(p.hasOpenViews()){
						arg0.cancel();
						break;
					}
				}
				
			}
			
			@Override
			public void closed(CVetoClosingEvent arg0) {
				// TODO Auto-generated method stub
				
			}
		});
		
		Main.getControl().addDockable(this);
		setResizeRequest(new RequestDimension(300,true),true);
		setResizeLockedHorizontally(true);
		setVisible(true);        
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

	public PatchLibrary getLibrary() {
		return library;
	}

	public void redraw() {
		list.invalidate();
		list.repaint();
	}
}

