package org.pale.stumpy2.model.paramtypes;

import java.util.List;

import javax.swing.JComponent;

import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ParameterChangeListener;

public class StringParam extends Parameter {

	public StringParam(String name,String initial) {
		super(name);
		setEncodedValue(initial);
	}
	
    /**
     * Write a command to send this parameter's value to the server.
     * This version uses the stored string mechanism, sending the command as two strings.
     * This permits longer strings with spaces.
     * @param cmds the list of commands to add the command to
     * @param patchid the ID of the patch containing the component
     * @param componentid the ID of the component containing the param
     * @param paramidx  the index of the param within the component
     */
	@Override
    public void writeSyncCommand(List<String> cmds, int patchid, int componentid) {
		cmds.add(":0"+getEncodedValue());
        cmds.add("pss "+patchid+" "+componentid+" "+getID()+" "+getCodeChar()+" 0");
    }

	@Override
	public Memento createMemento() {
        Memento m = new Memento();
        setCoreMemento(m);
        return m;
    }

    static public class Memento extends Parameter.Memento{

        @Override
        public Parameter create() {
            Parameter p=new StringParam(getName(),getEncodedValue());
            p.setID(getID());
            return p;
        }
    }

	@Override
	public char getCodeChar() {
		return 's';
	}

	@Override
	public JComponent createControl(
			ParameterChangeListener parameterChangeListener) {
        return new StringEditor(this,parameterChangeListener);
	}

}
