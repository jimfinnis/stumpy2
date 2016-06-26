package org.pale.stumpy2.model.paramtypes;

import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.Hashtable;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.Patch;

public class IntegerEditor extends JPanel implements ChangeListener {
    private Parameter param;
    private JLabel valueLabel;
    private ParameterChangeListener paramChangeListener;
    
    /**
     * Create the new integer editor widget, getting the initial value of the editor from the
     * encoded value in the parameter.
     * @param patch 
     * @param p the parameter we are editing
     * @param pc 
     */
    IntegerEditor(IntParam p, ParameterChangeListener pc){
        super(new FlowLayout());
        
        param = p;
        paramChangeListener=pc;
        
        // numbers are min,max,default
        JSlider slider = new JSlider(JSlider.HORIZONTAL,p.getMinVal(),p.getMaxVal(),Integer.parseInt(p.getEncodedValue()));
        Hashtable<Integer,JLabel> labelTable = new Hashtable<Integer,JLabel>();
        labelTable.put(new Integer(p.getMinVal()), new JLabel(Integer.toString(p.getMinVal())));
        labelTable.put(new Integer(p.getMaxVal()), new JLabel(Integer.toString(p.getMaxVal())));
        slider.setLabelTable(labelTable);
        slider.setPaintLabels(true);
        slider.addChangeListener(this);
        add(slider);
        
        add(new JLabel(p.getName()));
        
        valueLabel = new JLabel(p.getEncodedValue());
        add(valueLabel);

        setVisible(true);
    }

    /**
     * Handle state changes, setting the parameter encoded value.
     */
    @Override
    public void stateChanged(ChangeEvent arg0) {
        JSlider slider = (JSlider) arg0.getSource();
        if(!slider.getValueIsAdjusting()){
            int val = (int)slider.getValue();
            param.setEncodedValue(Integer.toString(val));
            valueLabel.setText(param.getEncodedValue());
            valueLabel.revalidate();
            valueLabel.repaint();
            paramChangeListener.onChange(param);
        }
    }
}
