package org.pale.stumpy.componentview;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.List;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ParameterChangeListener;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.PatchChangeListener.PatchChange;
import org.pale.stumpy.model.PatchChangeListener.PatchChangeType;

/**
 * This is a view of a component, showing the input and output names and
 * allowing the parameters to be edited by producing a set of parameter editors.
 * @author white
 *
 */
public class ComponentView extends JFrame  {

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
    public ComponentView(Patch patch, Component component) {
        this.component = component;

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        Container pane = getContentPane();

        pane.setLayout(new GridBagLayout());
        
        GridBagConstraints c = new GridBagConstraints();
        c.gridx=0;
        c.gridy=0;

        setTitle(component.getType().getName());

        // add the inputs/outputs legend

        JPanel ptmp = new JPanel(new FlowLayout());
        ptmp.add(buildLegend("inputs", component.getType().getAllInputNames()));
        ptmp.add(buildLegend("outputs", component.getType().getAllOutputNames()));
        pane.add(ptmp,c);
        c.gridy++;
        

        // now add the components! Also create an object to handle when we get a parameter change, and 
        // tell the patch
        List<JComponent> list = component.createEditors(patch,new ParameterChangeListener(component,patch) {
            @Override
            public void onChange(Parameter p) {
                getPatch().update(new PatchChange(PatchChangeType.PARAMETER,getComponent(),p));
            }
        });
        
        for (JComponent comp : list) {
            pane.add(comp,c);
            c.gridy++;
        }

        //setMinimumSize(new Dimension(40, 40));

        pack();
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
