package org.pale.stumpy2.componentview;

import java.awt.Container;

import javax.swing.BoxLayout;

import org.pale.stumpy2.Main;
import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.ui.ControlledDockable;
import org.pale.stumpy2.ui.support.Images;

public class ComponentBoxView extends ControlledDockable {

	private Container pane;
	public ComponentBoxView() {
		super("compbox");
		setTitleIcon(Images.createImageIcon("icons/bricks"));
		setResizeLockedHorizontally(true);
		Main.getControl().addDockable(this);
		pane = getContentPane();
		pane.setLayout(new BoxLayout(pane,BoxLayout.PAGE_AXIS));
		setVisible(true);        
	}

	public void add(Patch p,Component c){
		ComponentPanel cp = new ComponentPanel(p,c);
		pane.add(cp);
		pane.validate();
		pane.repaint();
	}
}
