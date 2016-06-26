package org.pale.stumpy2.ui;

import java.awt.Component;
import java.awt.event.ActionListener;

import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JMenuItem;

import org.pale.stumpy2.ui.support.ComponentCommandBindings;
import org.pale.stumpy2.ui.support.UIElement;
import org.pale.stumpy2.ui.support.Images;

import bibliothek.gui.dock.common.EnableableItem;
import bibliothek.gui.dock.common.action.CButton;
import bibliothek.gui.dock.toolbar.CToolbarItem;
import bibliothek.gui.dock.toolbar.expand.ExpandedState;

public class ToolbarButton extends CToolbarItem implements UIElement {

	private JButtonElement jbut;
	private CButtonElement cbut;
	
    /// wrapper class because we need a subclass of UIElement
    class JButtonElement extends JButton implements UIElement {
		public JButtonElement(String name,Icon icon) {
			super(name,icon);
		}
    }
    class CButtonElement extends CButton implements UIElement {
		public CButtonElement(String name,Icon icon) {
			super(name,icon);
		}
    }


	public ToolbarButton(String id, String text, String iconname) {
		super(id);

		Icon icon = Images.createImageIcon(iconname);
		intern().setTitleText(text);
		
		cbut = new CButtonElement(null,icon);
		setItem(cbut);
		
		jbut = new JButtonElement(text,icon);
		setItem(jbut,ExpandedState.STRETCHED);
		
		setEnabled(true);
	}
	
	public void addBindings(ComponentCommandBindings a, String command){
		jbut.addActionListener(a); 
		cbut.addActionListener(a);
		a.add(jbut, command);
		a.add(cbut, command);
		
	}
	
	@Override
	public void setEnabled(boolean enabled){
		jbut.setEnabled(enabled);
		cbut.setEnabled(enabled);
		setEnabled(EnableableItem.ALL,enabled); // probly does both the above anyway
	}

	public void removeFromBindings(ComponentCommandBindings bindings) {
		jbut.removeActionListener(bindings);
		cbut.removeActionListener(bindings);
		bindings.remove(cbut);
		bindings.remove(jbut);
	}
}
