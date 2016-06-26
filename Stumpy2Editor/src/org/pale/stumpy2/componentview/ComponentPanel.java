package org.pale.stumpy2.componentview;

import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener.PatchChange;
import org.pale.stumpy2.model.PatchChangeListener.PatchChangeType;

public class ComponentPanel extends JPanel {
    /**
     * the patch this component is in
     */
    private Patch patch;
    /**
     * The component we're viewing
     */
    private Component component;

    /**
     * Constructor 
     * @param patch the patch the component is in
     * @param component the component to edit
     */
    public ComponentPanel(final Patch patch, final Component component) {
        this.component = component;


        setLayout(new GridBagLayout());
        
        GridBagConstraints c = new GridBagConstraints();
        c.gridx=0;
        c.gridy=0;
        
        JLabel titleBox = new JLabel(component.getType().getName());
        titleBox.setOpaque(true);
        titleBox.setBackground(Color.DARK_GRAY);
        add(titleBox,c);c.gridy++;

//        setTitle(component.getType().getName());

        // add the inputs/outputs

        JPanel ptmp = new JPanel(new FlowLayout());
        // inputs is just a list of names
        ptmp.add(buildLegend("inputs", component.getType().getAllInputNames()));
        // outputs have buttons, indicating whether the system should run
        // the component always when that output is invoked, or whether it should
        // only run it the first time in a frame (doesn't always apply - e.g.
        // rendering prims always run always).
        
        JPanel outputPanel = new JPanel();
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
        add(ptmp,c);
        c.gridy++;
        
        

        // now add the parameters! Also create an object to handle when we get a parameter change, and 
        // tell the patch
        List<JComponent> list = component.createEditors(patch,new ParameterChangeListener(component,patch) {
            @Override
            public void onChange(Parameter p) {
                getPatch().update(new PatchChange(PatchChangeType.PARAMETER,getComponent(),p));
            }
        });
        
        for (JComponent comp : list) {
            add(comp,c);
            c.gridy++;
        }

        //setMinimumSize(new Dimension(40, 40));
        setVisible(true);
    }

    /**
     * Construct, as component, a text view describing the inputs and outputss 
     * @param header
     * @param nameList
     * @return a text component of some kind.
     */
    private java.awt.Component buildLegend(String header, List<String> nameList) {
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
}
