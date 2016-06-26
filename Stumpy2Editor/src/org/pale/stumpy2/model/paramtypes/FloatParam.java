package org.pale.stumpy2.model.paramtypes;

import javax.swing.JComponent;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.paramtypes.IntParam.Memento;

public class FloatParam extends Parameter {

    public double getMinVal() {
        return minVal;
    }


    public void setMinVal(double minVal) {
        this.minVal = minVal;
    }

    public double getMaxVal() {
        return maxVal;
    }

    public void setMaxVal(double maxVal) {
        this.maxVal = maxVal;
    }		

    private double minVal;
    private double maxVal;

    public FloatParam(String name, double min, double max, double initial) {
        super(name);
        setEncodedValue(Double.toString(initial));
        minVal = min;
        maxVal = max;
    }
    
    public char getCodeChar(){
        return 'f';
    }
    
    static public class Memento extends Parameter.Memento {
        private double minVal;
        private double maxVal;
        public double getMinVal() {
            return minVal;
        }
        public void setMinVal(double minVal) {
            this.minVal = minVal;
        }
        public double getMaxVal() {
            return maxVal;
        }
        public void setMaxVal(double maxVal) {
            this.maxVal = maxVal;
        }
        @Override
        public Parameter create() {
            Parameter p = new FloatParam(getName(),getMinVal(),getMaxVal(),Double.parseDouble(getEncodedValue()));
            p.setID(getID());
            return p;
        }
    }

    @Override
    public Parameter.Memento createMemento() {
        Memento m = new Memento();
        setCoreMemento(m);
        m.setMinVal(minVal);
        m.setMaxVal(maxVal);
        return m;
    }

    @Override
    public JComponent createControl(ParameterChangeListener pc) {
        return new FloatEditor(this,pc);
    }

}
