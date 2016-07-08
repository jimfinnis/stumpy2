package org.pale.stumpy2.model.paramtypes;

import java.awt.FlowLayout;
import java.text.DecimalFormat;
import java.util.Hashtable;

import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;

import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.paramtypes.EnvelopeParam.Envelope;

public class EnvelopeEditor extends JPanel  {
	
	static final int MAXINTVAL=1000;
	static final float MAXTIME=10;

	
    /**
     * convert from an integer (as used by the slider) to a float in the appropriate range
     * @param v the integer value between 0 and MAXINTVAL
     * @return the double value between the parameter's min and max
     */
    private double getValueFromInt(int v,float mn,float mx){
        double f = v;
        f /= (MAXINTVAL); // value is now 0-1
        f *= (mx-mn); // value is now 0 - (max-min)
        f += mn; // value is now min-max
        return f;
    }
    
    /**
     * convert from a float in the appropriate range to an integer (as used by the slider) 
     * @param v the double value between the parameter's min and max
     * @return the integer value between 0 and MAXINTVAL
     */
    private int getIntFromValue(double f,float mn,float mx){
        f -= mn;
        f /= (mx-mn);
        f *= MAXINTVAL;
        return (int)f;
    }

    static DecimalFormat formatter = new DecimalFormat("###.##");

	private ParameterChangeListener pc;
	private EnvelopeParam param;
	
	JSlider[] slidersT = new JSlider[EnvelopeParam.ENVSIZE];
	JSlider[] slidersL = new JSlider[EnvelopeParam.ENVSIZE];
	
	JTextField[] textsT = new JTextField[EnvelopeParam.ENVSIZE];
	JTextField[] textsL = new JTextField[EnvelopeParam.ENVSIZE];
	String[] lastGoodStringsT = new String[EnvelopeParam.ENVSIZE];
	String[] lastGoodStringsL = new String[EnvelopeParam.ENVSIZE];
	
	public EnvelopeEditor(EnvelopeParam envelopeParam,
			ParameterChangeListener pc) {
		super();
		param = envelopeParam;
		setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		this.pc = pc;
		
		// create the sub-editor for each env point
		
		Envelope e = param.val;
		for(int i=0;i<EnvelopeParam.ENVSIZE;i++){
			JPanel subp = new JPanel(new FlowLayout()); // horizontal panel for both time and level
	        subp.add(new JLabel(Integer.toString(i)));
	        
			JSlider slider;
	        slider = new JSlider(JSlider.HORIZONTAL,0,MAXINTVAL,getIntFromValue(e.times[i],0,MAXTIME));
	        Hashtable<Integer,JLabel> labelTable = new Hashtable<Integer,JLabel>();
	        labelTable.put(new Integer(getIntFromValue(0,0,MAXTIME)), new JLabel(formatter.format(0)));
	        labelTable.put(new Integer(getIntFromValue(MAXTIME,0,MAXTIME)), new JLabel(formatter.format(MAXTIME)));
	        slider.setLabelTable(labelTable);
	        slider.setPaintLabels(true);
//	        slider.addChangeListener(this);
	        subp.add(slider);
	        slidersT[i]=slider;
	        
	        lastGoodStringsT[i] = formatter.format(e.times[i]);
	        JTextField valueEdit = new JTextField(lastGoodStringsT[i],10);
//	        valueEdit.addKeyListener(this);
	        textsT[i] = valueEdit;
	        subp.add(valueEdit);

	        
	        slider = new JSlider(JSlider.HORIZONTAL,0,MAXINTVAL,getIntFromValue(e.levels[i],-1,1));
	        labelTable = new Hashtable<Integer,JLabel>();
	        labelTable.put(new Integer(getIntFromValue(-1,-1,1)), new JLabel(formatter.format(-1)));
	        labelTable.put(new Integer(getIntFromValue(1,-1,1)), new JLabel(formatter.format(1)));
	        slider.setLabelTable(labelTable);
	        slider.setPaintLabels(true);
//	        slider.addChangeListener(this);
	        subp.add(slider);
	        slidersL[i]=slider;
	        
	        lastGoodStringsL[i] = formatter.format(e.levels[i]);
	        valueEdit = new JTextField(lastGoodStringsL[i],10);
//	        valueEdit.addKeyListener(this);
	        textsL[i] = valueEdit;
	        subp.add(valueEdit);
	        
	        add(subp);
		}
		setVisible(true);
	}

}
