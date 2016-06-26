package org.pale.stumpy2.model.paramtypes;

import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.text.DecimalFormat;
import java.util.Hashtable;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener.PatchChange;

/**
 * An editor for FloatParam, using an integer slider over a fixed range mapped to the final double range by
 * a pair of methods.
 * @author white
 *
 */
@SuppressWarnings("serial")
public class FloatEditor extends JPanel implements ChangeListener, KeyListener {
    private FloatParam param;
    private JTextField valueEdit;
    private double range;
    private String lastGoodString; 
    
    static DecimalFormat formatter = new DecimalFormat("###.##");
    
    /** the integer to which the maximum value is mapped. Min is always mapped to zero*/
    static final int MAXINTVAL = 1000;
    
    DecimalFormat format;
    private ParameterChangeListener paramChangeListener;
    private JSlider slider;
    
    /**
     * convert from an integer (as used by the slider) to a float in the appropriate range
     * @param v the integer value between 0 and MAXINTVAL
     * @return the double value between the parameter's min and max
     */
    private double getValueFromInt(int v){
        double f = v;
        f /= (MAXINTVAL); // value is now 0-1
        f *= range; // value is now 0 - (max-min)
        f += param.getMinVal(); // value is now min-max
        return f;
    }
    
    /**
     * convert from a float in the appropriate range to an integer (as used by the slider) 
     * @param v the double value between the parameter's min and max
     * @return the integer value between 0 and MAXINTVAL
     */
    private int getIntFromValue(double f){
        f -= param.getMinVal();
        f /= range;
        f *= MAXINTVAL;
        return (int)f;
    }
    
    /**
     * Create the new integer editor widget, getting the initial value of the editor from the
     * encoded value in the parameter.
     * @param patch 
     * @param p the parameter we are editing
     * @param pc 
     */
    FloatEditor(FloatParam p, ParameterChangeListener pc){
        super(new FlowLayout());

        paramChangeListener = pc;
        
        param = p;
        range = param.getMaxVal() - param.getMinVal();
        
        // we set up a 0 to MAXINTVAL slider
        
        slider = new JSlider(JSlider.HORIZONTAL,0,MAXINTVAL,getIntFromValue(Double.parseDouble(p.getEncodedValue())));
        Hashtable<Integer,JLabel> labelTable = new Hashtable<Integer,JLabel>();
        labelTable.put(new Integer(getIntFromValue(p.getMinVal())), new JLabel(formatter.format(p.getMinVal())));
        labelTable.put(new Integer(getIntFromValue(p.getMaxVal())), new JLabel(formatter.format(p.getMaxVal())));
        slider.setLabelTable(labelTable);
        slider.setPaintLabels(true);
        slider.addChangeListener(this);
        add(slider);
        
        add(new JLabel(p.getName()));
        
        double f = Double.parseDouble(p.getEncodedValue());
        System.out.println(f);
        lastGoodString = formatter.format(f);
        valueEdit = new JTextField(lastGoodString,10);
        valueEdit.addKeyListener(this);
        add(valueEdit);
        
        setVisible(true);
    }

    /**
     * Handle state changes, setting the parameter encoded value.
     */
    @Override
    public void stateChanged(ChangeEvent arg0) {
        if(!slider.getValueIsAdjusting()){
            double val = getValueFromInt(slider.getValue());
            param.setEncodedValue(Double.toString(val));
            valueEdit.setText(formatter.format(val));
            valueEdit.revalidate();
            valueEdit.repaint();
            paramChangeListener.onChange(param);
        }
    }

    @Override
    public void keyPressed(KeyEvent arg0) {
        if(arg0.getKeyCode()==KeyEvent.VK_ENTER){
            try {
                double val = Double.parseDouble(valueEdit.getText());
                if(val >= param.getMinVal() && val <= param.getMaxVal()){
                    param.setEncodedValue(Double.toString(val));
                    slider.setValue(getIntFromValue(val));
                    lastGoodString = formatter.format(val);
                }
            } catch(NumberFormatException e){
                // does nothing but skip a few things
            }
            valueEdit.setText(lastGoodString);
        }
        
    }

    @Override
    public void keyReleased(KeyEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void keyTyped(KeyEvent arg0) {
        // TODO Auto-generated method stub
        
    }
}
