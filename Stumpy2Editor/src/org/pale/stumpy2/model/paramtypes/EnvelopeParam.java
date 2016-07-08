package org.pale.stumpy2.model.paramtypes;

import javax.swing.JComponent;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;

public class EnvelopeParam extends Parameter {
	
	public static int ENVSIZE=4; // must agree with server side.
	public static class Envelope {
		
		float[] times;;
		float[] levels;
		public Envelope(){
			times = new float[ENVSIZE];
			levels = new float[ENVSIZE];			
		}
		
		public Envelope(String s){
			times = new float[ENVSIZE];
			levels = new float[ENVSIZE];			
			s=s.substring(0, s.length()-1);
			String nums[] = s.split(",");
			for(int i=0;i<nums.length;i+=2){
				times[i/2]=Integer.parseInt(nums[i]);
				levels[i/2]=Integer.parseInt(nums[i+1]);
			}
		}
		public String getString(){
			String out = "";
			for(int i=0;i<ENVSIZE;i++){
				out+=times[i]; out+=",";
				out+=levels[i];
				out+=(i==ENVSIZE-1)?";":",";
			}
			return out;
		}
	}

	Envelope val;
	public EnvelopeParam(String name, String string) {
		super(name);
		val = new Envelope(string);
		setEncodedValue(string);
	}
	
	static public class Memento extends Parameter.Memento {

		@Override
		public Parameter create() {
			Parameter p = new EnvelopeParam(getName(),getEncodedValue());
			p.setID(getID());
			return p;
		}
		
	}

	@Override
	public Memento createMemento() {
		Memento m = new Memento();
		setCoreMemento(m);
		return m;
	}

	@Override
	public char getCodeChar() {
		return 'E';
	}

	@Override
	public JComponent createControl(
			ParameterChangeListener pc) {
		return new EnvelopeEditor(this,pc);
	}

}
