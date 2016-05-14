package org.pale.stumpy.model.paramtypes;

import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.pale.stumpy.model.ParameterChangeListener;

/**
 * The editor for enumerations - it's a drop down box.
 * @author white
 *
 */
public class EnumEditor extends JPanel  {

    private ParameterChangeListener parameterChangeListener;
    private JComboBox box;

    public EnumEditor(final EnumParam enumParam,
            ParameterChangeListener pc) {
        
        super(new FlowLayout());
        parameterChangeListener = pc;

        box = new JComboBox(enumParam.getValueArray());
        add(box);
        add(new JLabel(enumParam.getName()));
        
        box.setSelectedIndex(Integer.parseInt(enumParam.getEncodedValue()));
        
        setVisible(true);
        
        // When the value changes, we need to tell both the parameter itself
        // and any parameter change listener which also should be told.
        
        box.addActionListener(new ActionListener() {
            
            @Override
            public void actionPerformed(ActionEvent arg0) {
                int idx = box.getSelectedIndex();
                enumParam.setEncodedValue(Integer.toString(idx));
                parameterChangeListener.onChange(enumParam);
            }
        });
    }
}
