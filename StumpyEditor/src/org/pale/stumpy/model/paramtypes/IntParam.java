package org.pale.stumpy.model.paramtypes;

import javax.swing.JComponent;

import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ParameterChangeListener;
import org.pale.stumpy.model.Patch;

/**
 * An integer parameter type
 * @author white
 *
 */
public class IntParam extends Parameter {

    public int getMinVal() {
        return minVal;
    }

    public int getMaxVal() {
        return maxVal;
    }
    
    

    private int minVal;
    private int maxVal;

    /**
     * Constructor; will add to ParameterType's static map
     */
    public IntParam(String name, int min, int max, int initial){
        super(name);
        setEncodedValue(Integer.toString(initial));
        minVal = min;
        maxVal = max;
    }
    
    public char getCodeChar(){
        return 'i';
    }


    @Override
    public JComponent createControl(ParameterChangeListener pc) {
        return new IntegerEditor(this,pc);
    }

    @Override
    public Parameter.Memento createMemento() {
        Memento m = new Memento();
        setCoreMemento(m);
        m.setMinVal(minVal);
        m.setMaxVal(maxVal);
        return m;
    }
    
    static public class Memento extends Parameter.Memento {
        public Memento(){}
        public int getMinVal() {
            return minVal;
        }
        public void setMinVal(int minVal2) {
            this.minVal = minVal2;
        }
        public int getMaxVal() {
            return maxVal;
        }
        public void setMaxVal(int maxVal2) {
            this.maxVal = maxVal2;
        }
        @Override
        public Parameter create() {
            Parameter p = new IntParam(getName(),getMinVal(),getMaxVal(),Integer.parseInt(getEncodedValue()));
            p.setID(getID());
            return p;
        }

        private int minVal;
        private int maxVal;
        
    }
}
