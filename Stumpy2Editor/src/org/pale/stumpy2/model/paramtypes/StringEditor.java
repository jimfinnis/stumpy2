package org.pale.stumpy2.model.paramtypes;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;

public class StringEditor extends JPanel implements ActionListener {
    private Parameter param;
    private ParameterChangeListener paramChangeListener;

    StringEditor(StringParam p, ParameterChangeListener listener){
        super(new FlowLayout());
        param = p;
        paramChangeListener=listener;
        
        JLabel name = new JLabel(p.getName());
        add(name);
        JTextField tf = new JTextField(p.getEncodedValue(),40);
        tf.addActionListener(this);
        add(tf);
        
        setVisible(true);
    }

	@Override
	public void actionPerformed(ActionEvent arg0) {
		JTextField tf = (JTextField)arg0.getSource();
		param.setEncodedValue(tf.getText());
		paramChangeListener.onChange(param);
	}
    

}
