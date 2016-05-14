package org.pale.stumpy.model.paramtypes;

import javax.swing.JComponent;

import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ParameterChangeListener;
import org.pale.stumpy.model.paramtypes.IntParam.Memento;

/**
 * Enumerated parameter - it's actually sent to the server as an int, and exists there
 * as an integer parameter.
 * @author white
 *
 */
public class EnumParam extends Parameter {
    
    private int maxVal;
    private String[] valueArray;
    
    public int getMaxVal(){
        return maxVal;
    }
    
    public String[] getValueArray(){
        return valueArray;
    }
    
    public EnumParam(String name,String[] values, int initialIdx){
        super(name);
        setEncodedValue(Integer.toString(initialIdx));
        valueArray = values;
        maxVal = values.length-1;
    }

    @Override
    public Memento createMemento() {
        Memento m = new Memento();
        setCoreMemento(m);
        m.setValueArray(valueArray);
        return m;
    }
    
    static public class Memento extends Parameter.Memento {
        public Memento(){}

        @Override
        public Parameter create() {
            Parameter p = new EnumParam(getName(),valueArray,Integer.parseInt(getEncodedValue()));
            p.setID(getID());
            return p;
        }

        private String[] valueArray;
        public String[] getValueArray() {
            return valueArray;
        }
        public void setValueArray(String[] valueArray) {
            this.valueArray = valueArray;
        }

    }

    @Override
    public char getCodeChar() {
        return 'i'; // same as IntParam
    }

    @Override
    public JComponent createControl(
            ParameterChangeListener parameterChangeListener) {
        return new EnumEditor(this,parameterChangeListener);
    }

}
