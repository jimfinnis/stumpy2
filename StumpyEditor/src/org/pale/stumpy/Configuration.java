package org.pale.stumpy;

import java.awt.Color;
import java.io.IOException;

import org.pale.stumpy.client.Client;
import org.pale.stumpy.client.Client.CommsResult;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ComponentTypeRegistry;
import org.pale.stumpy.model.ConnectionType;
import org.pale.stumpy.model.Parameter;
import org.pale.stumpy.model.ProtocolException;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.model.paramtypes.BoolParam;
import org.pale.stumpy.model.paramtypes.FloatParam;
import org.pale.stumpy.model.paramtypes.IntParam;

/**
 * This class contains static methods setting up the configuration, typically
 * creating new value and component types. 
 * @author white
 *
 */
public class Configuration {

	public static void initialise() {

		// create the value types
		ConnectionType.create("flow",'f', Color.BLACK);
		ConnectionType.create("float", 'n', Color.BLUE);
	}

	/// this is a synchronous chat with the server to load the initial
	/// configuration data
	public static void readConfiguration(Client c) throws UnknownComponentTypeException, IOException, ProtocolException{
		c.doSend("startcomps");
		boolean compsDone = false;

		while(!compsDone){
			CommsResult r = c.syncRead();
			switch(r.code){
			case 410: // new component
				String bits[] = r.status.split(":",4);
				String name = bits[0];
				String inputs = bits[1];
				String outputs = bits[2];
				int paramct = Integer.parseInt(bits[3]);
				System.out.println("Component:"+name+" Inputs:"+inputs+
						" Outputs:"+outputs+" ParamCount:"+paramct);
				ComponentType ct = new ComponentType(name,"category",70,30);
				// create the inputs
				for(int i=0;i<inputs.length();i++){
					char cc = inputs.charAt(i);
					if(cc=='i')break;
					ConnectionType contype = ConnectionType.get(cc);
					ct.addInput(contype, "anon");
				}
				// and the outputs
				for(int i=0;i<outputs.length();i++){
					char cc = outputs.charAt(i);
					if(cc=='i')break;
					ConnectionType contype = ConnectionType.get(cc);
					ct.addOutput(contype, "anon");
				}
				// get the params
				for(int i=0;i<paramct;i++){
					c.doSend("compparam "+i);
					CommsResult pr = c.syncRead();
					if(pr.code != 412)
						throw new ProtocolException("Unexpected message "+pr.code);
					System.out.println("Param "+i+" desc:"+pr.status);

					Parameter p = createParamFromDesc(pr.status);
					ct.addParameter(p);
				}
				ct.layout();
				ComponentTypeRegistry.getInstance().add(ct);

				c.doSend("nextcomp");		
				break;
			case 411:
				compsDone=true;
				break;
			default:
				throw new ProtocolException("Unexpected message "+r.code);
			}
			System.out.println("configuration read done");
		}
	}

	private static Parameter createParamFromDesc(String status) throws ProtocolException {
		String s[] = status.split(":");
		Parameter p = null;
		switch(s[0].charAt(0)){
		case 'f':
			p = new FloatParam(s[1], Float.parseFloat(s[2]), 
					Float.parseFloat(s[3]), Float.parseFloat(s[4]));
			break;
		case 'i':
			p = new IntParam(s[1], Integer.parseInt(s[2]), 
					Integer.parseInt(s[3]), Integer.parseInt(s[4]));
			break;
		case 'b':
			p = new BoolParam(s[1], s[2].charAt(0)=='y');
			break;
		case 'e':
			break; // Hm.
		default:
			throw new ProtocolException("bad parameter type: "+s[0]);
		}
		return p;
	}


}
