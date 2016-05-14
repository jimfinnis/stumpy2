package org.pale.stumpy.model.paramtypes;

import javax.swing.JComponent;

import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ParameterChangeListener;

public class BoolParam extends Parameter {

    public BoolParam(String name,boolean initial) {
        super(name);
        setEncodedValue(initial?"y":"n");
    }

    @Override
    public Parameter.Memento createMemento() {
        Memento m = new Memento();
        setCoreMemento(m);
        return m;
    }
    
    static public class Memento extends Parameter.Memento{

        @Override
        public Parameter create() {
            Parameter p=new BoolParam(getName(),getEncodedValue().equals("y"));
            p.setID(getID());
            return p;
            
        }
        
    }

    @Override
    public char getCodeChar() {
        return 'b';
    }

    @Override
    public JComponent createControl(
            ParameterChangeListener parameterChangeListener) {
        return new BoolEditor(this,parameterChangeListener);
    }

}
