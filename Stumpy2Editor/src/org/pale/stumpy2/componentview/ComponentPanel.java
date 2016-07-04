package org.pale.stumpy2.componentview;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.HashSet;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener.PatchChange;
import org.pale.stumpy2.model.PatchChangeListener.PatchChangeType;
import org.pale.stumpy2.ui.support.Images;

public class ComponentPanel extends JPanel  {
    /**
     * the patch this component is in
     */
    private Patch patch;
    /**
     * The component we're viewing
     */
    private Component component;
	private boolean selected=true;
	private JPanel titleBox;
	private JPanel contents;
	private JButton hideButton;



    /**
     * Constructor 
     * @param patch the patch the component is in
     * @param component the component to edit
     */
    public ComponentPanel(final Patch patch,final Component component) {
        this.component = component;
        this.patch = patch;


        setLayout(new GridBagLayout());
        
        GridBagConstraints c = new GridBagConstraints();
        c.gridx=0;
        c.gridy=0;
        c.weightx=1;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.anchor = GridBagConstraints.WEST;
        
        titleBox = new JPanel(new BorderLayout());
        JLabel lab = new JLabel(component.getType().getName());
        lab.setForeground(Color.WHITE);
        titleBox.add(lab,BorderLayout.WEST);
        JPanel butpanel = new JPanel(new FlowLayout());
        hideButton = new JButton(null,Images.getImageIcon("icons/arrow_in"));
        final JButton closeButton = new JButton(null,Images.getImageIcon("icons/cancel"));
        butpanel.add(hideButton);
        butpanel.add(closeButton);
        titleBox.add(butpanel,BorderLayout.EAST);
        titleBox.setOpaque(true);
        titleBox.setBackground(selected?Color.RED: Color.GRAY);
        add(titleBox,c);
        
        hideButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(contents.isVisible()){
					hide();
				} else {
					reveal();
				}
			}
        });
        
        closeButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				HashSet<Component> s = new HashSet<Component>();
				s.add(component);
				ComponentBoxView.getInstance().removeSet(s);
			}
        });

        // title bar done, everything else goes into the hideable subpanel
        
        contents = new JPanel(new GridBagLayout());
        c.gridy=0; // we're inside a new layout, so start again

        JPanel ptmp = new JPanel();
        ptmp.setLayout(new BoxLayout(ptmp,BoxLayout.LINE_AXIS));
        // inputs is just a list of names
        JComponent inpp = buildLegend("inputs", component.getType().getAllInputNames());
        inpp.setAlignmentY(TOP_ALIGNMENT);
        ptmp.add(inpp);
        
        // outputs have buttons, indicating whether the system should run
        // the component always when that output is invoked, or whether it should
        // only run it the first time in a frame (doesn't always apply - e.g.
        // rendering prims always run always).
        
        JPanel outputPanel = new JPanel();
        outputPanel.setAlignmentY(TOP_ALIGNMENT);
        outputPanel.setLayout(new BoxLayout(outputPanel,BoxLayout.PAGE_AXIS));
        outputPanel.add(new JLabel("<html><u>outputs/runalways</u></html>"));
        List<String> opnames = component.getType().getAllOutputNames();
        for(int i=0;i<opnames.size();i++){
        	final int index = i;
        	final JCheckBox ch=new JCheckBox(opnames.get(i));
        	ch.setSelected(false);
        	ch.addItemListener(new ItemListener(){
				@Override
				public void itemStateChanged(ItemEvent arg0) {
					boolean state = ch.isSelected();
					component.setRunOutputAlways(index,state);
	                patch.update(new PatchChange(PatchChangeType.RUNALWAYS,
	                		component,index));

					System.out.println("Output "+index+" now "+state);
				}
        	});
        	outputPanel.add(ch);
        }
        
        ptmp.add(outputPanel);
        contents.add(ptmp,c);
        // turn off filling, so the param editors align left.
        c.fill = GridBagConstraints.NONE;
        c.gridy++;

        // now add the parameters! Also create an object to handle when we get a parameter change, and 
        // tell the patch
        List<JComponent> list = component.createEditors(new ParameterChangeListener(component) {
            @Override
            public void onChange(Parameter p) {
                getPatch().update(new PatchChange(PatchChangeType.PARAMETER,getComponent(),p));
            }
        });
        
        for (JComponent comp : list) {
            contents.add(comp,c);
            c.gridy++;
        }

        c.gridy=1; // back in the outer layout, this is the second item
        add(contents,c);
        //setMinimumSize(new Dimension(40, 40));
        setVisible(true);
    }

    /**
     * Construct, as component, a text view describing the inputs and outputss 
     * @param header
     * @param nameList
     * @return a text component of some kind.
     */
    private JComponent buildLegend(String header, List<String> nameList) {
        int ct = 0;
        String s = "<html><u>" + header + "</u><br/>";
        for (String n : nameList) {
            s += "<p>" + n + "</p>";
            ct++;
        }
        s += "</html>";
        JLabel label = new JLabel(s, JLabel.LEFT);
        return label;
    }

	public void setSelected(boolean b) {
		selected = b;
        titleBox.setBackground(selected?Color.RED: Color.GRAY);
		titleBox.revalidate();
		titleBox.repaint();
	}
	
	public void hide(){
		if(contents.isVisible()){
			contents.setVisible(false);
			hideButton.setIcon(Images.getImageIcon("icons/arrow_out"));
			hideButton.repaint();
			revalidate();
			repaint();
		}
	}
	
	public void reveal(){
		if(!contents.isVisible()){
			contents.setVisible(true);
			hideButton.setIcon(Images.getImageIcon("icons/arrow_in"));
			hideButton.repaint();
			revalidate();
			repaint();
		}
	}

}
