package org.pale.stumpy2.model.paramtypes;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.text.DecimalFormat;
import java.util.Hashtable;

import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.paramtypes.EnvelopeParam.Envelope;

public class EnvelopeEditor extends JPanel  {
	
	private boolean insideKeyPress;

	public class LevelTextListener implements KeyListener {
		JTextField t;int idx;
		public LevelTextListener(JTextField t, int i) {
			this.t = t;
			this.idx = i;
		}

		@Override
		public void keyPressed(KeyEvent e) {
	        if(e.getKeyCode()==KeyEvent.VK_ENTER){
	            try {
	            	insideKeyPress=true;
	                float val = Float.parseFloat(t.getText());
	                if(val >= -1 && val <= 1){
	                    // param.setEncodedValue(Double.toString(val));
	                    slidersL[idx].setValue(getIntFromValue(val,-1,1));
	                    lastGoodStringsL[idx] = formatter.format(val);
	                    param.val.levels[idx] = val;
	                    sanitiseValue();
	                    param.encode();
	                    graph.repaint();
	                    pc.onChange(param);
	                }
	            } catch(NumberFormatException ex){
	                // does nothing but skip a few things
	            }
	            t.setText(lastGoodStringsL[idx]);
	            insideKeyPress=false;
	        }
		}

		@Override
		public void keyReleased(KeyEvent e) {}
		@Override
		public void keyTyped(KeyEvent e) {}

	}

	public class TimeTextListener implements KeyListener {
		JTextField t;int idx;
		public TimeTextListener(JTextField t, int i) {
			this.t = t;
			this.idx = i;
		}

		@Override
		public void keyPressed(KeyEvent e) {
	        if(e.getKeyCode()==KeyEvent.VK_ENTER){
	            try {
	            	insideKeyPress=true;
	                float val = Float.parseFloat(t.getText());
	                if(val >= 0 && val <= MAXTIME){
	                    param.val.times[idx] = val;
	                    sanitiseValue();
	                    slidersT[idx].setValue(getIntFromValue(param.val.times[idx],0,MAXTIME));
	                    lastGoodStringsT[idx] = formatter.format(param.val.times[idx]);
	                    param.encode();
	                    graph.repaint();
	                    pc.onChange(param);
	                }
	            } catch(NumberFormatException ex){
	                // does nothing but skip a few things
	            }
	            t.setText(lastGoodStringsT[idx]);
	            insideKeyPress=false;
	        }
		}

		@Override
		public void keyReleased(KeyEvent e) {}
		@Override
		public void keyTyped(KeyEvent e) {}
	}

	public class LevelSliderChangeListener implements ChangeListener {
		private JSlider slider;
		private int idx;
		public LevelSliderChangeListener(JSlider slider, int i) {
			this.slider = slider;
			this.idx = i;
		}

		@Override
		public void stateChanged(ChangeEvent e) {
			if(!slider.getValueIsAdjusting() && !insideKeyPress){
				double val = getValueFromInt(slider.getValue(), -1, 1);
				param.val.levels[idx] = (float)val;
				textsL[idx].setText(formatter.format(val));
				textsL[idx].revalidate();
				textsL[idx].repaint();
                graph.repaint();
                param.encode();
				pc.onChange(param);
			}
		}
	}

	public class TimeSliderChangeListener implements ChangeListener {
		private JSlider slider;
		private int idx;
		public TimeSliderChangeListener(JSlider slider, int i) {
			this.slider = slider;
			this.idx = i;
		}

		@Override
		public void stateChanged(ChangeEvent arg0) {
			if(!slider.getValueIsAdjusting() && !insideKeyPress){
				double val = getValueFromInt(slider.getValue(), 0, MAXTIME);
				param.val.times[idx] = (float)val;
				sanitiseValue();
				textsT[idx].setText(formatter.format(param.val.times[idx]));
				textsT[idx].revalidate();
				textsT[idx].repaint();
                param.encode();
                graph.repaint();
				pc.onChange(param);
			}
		}

	}

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
	private EnvelopePanel graph;
	
	public void setWidgetsFromValue(){
		Envelope e = param.val;
		for(int i=0;i<EnvelopeParam.ENVSIZE;i++){
			slidersT[i].setValue(getIntFromValue(e.times[i],0,MAXTIME));
			textsT[i].setText(formatter.format(e.times[i]));
			slidersL[i].setValue(getIntFromValue(e.levels[i],-1,1));
			textsL[i].setText(formatter.format(e.levels[i]));
		}
	}
		
	public void sanitiseValue(){
		Envelope e = param.val;
		boolean changed=false;
		for(int i=0;i<EnvelopeParam.ENVSIZE-1;i++){
			if(e.times[i]>e.times[i+1]){
				e.times[i+1]=e.times[i];
				changed=true;
			}
		}
		if(changed){
			insideKeyPress=true;
			setWidgetsFromValue();
			insideKeyPress=false;
		}
	}
	
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
	        slider.addChangeListener(new TimeSliderChangeListener(slider,i));
	        subp.add(slider);
	        slidersT[i]=slider;
	        
	        lastGoodStringsT[i] = formatter.format(e.times[i]);
	        JTextField valueEdit = new JTextField(lastGoodStringsT[i],10);
	        valueEdit.addKeyListener(new TimeTextListener(valueEdit,i));
	        textsT[i] = valueEdit;
	        subp.add(valueEdit);

	        
	        slider = new JSlider(JSlider.HORIZONTAL,0,MAXINTVAL,getIntFromValue(e.levels[i],-1,1));
	        labelTable = new Hashtable<Integer,JLabel>();
	        labelTable.put(new Integer(getIntFromValue(-1,-1,1)), new JLabel(formatter.format(-1)));
	        labelTable.put(new Integer(getIntFromValue(1,-1,1)), new JLabel(formatter.format(1)));
	        slider.setLabelTable(labelTable);
	        slider.setPaintLabels(true);
	        slider.addChangeListener(new LevelSliderChangeListener(slider,i));
	        subp.add(slider);
	        slidersL[i]=slider;
	        
	        lastGoodStringsL[i] = formatter.format(e.levels[i]);
	        valueEdit = new JTextField(lastGoodStringsL[i],10);
	        valueEdit.addKeyListener(new LevelTextListener(valueEdit,i));
	        textsL[i] = valueEdit;
	        subp.add(valueEdit);
	        
	        add(subp);
	        
		}
		graph = new EnvelopePanel(param.val);
		graph.setPreferredSize(new Dimension(300,150));
        add(graph);
		setVisible(true);
	}

}
