package org.pale.stumpy.model.paramtypes;

import java.awt.FlowLayout;
import java.util.Hashtable;

import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ParameterChangeListener;


public class BoolEditor extends JPanel implements ChangeListener {
    private Parameter param;
    private ParameterChangeListener paramChangeListener;

    BoolEditor(BoolParam p, ParameterChangeListener listener){
        super(new FlowLayout());
        param = p;
        paramChangeListener=listener;
        
        // numbers are min,max,default
        JCheckBox cb = new JCheckBox(p.getName(),p.getEncodedValue().equals("y"));
        cb.addChangeListener(this);
        add(cb);
        
        setVisible(true);
    }

    @Override
    public void stateChanged(ChangeEvent e) {
        JCheckBox s = (JCheckBox)e.getSource();
        if(s.isSelected())
            param.setEncodedValue("y");
        else
            param.setEncodedValue("n");
        paramChangeListener.onChange(param);
    }


}
