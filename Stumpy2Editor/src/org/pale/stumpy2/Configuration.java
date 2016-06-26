package org.pale.stumpy2;

import java.awt.Color;
import java.io.IOException;
import java.util.LinkedList;

import org.pale.stumpy2.client.Client;
import org.pale.stumpy2.client.Client.CommsResult;
import org.pale.stumpy2.model.ComponentType;
import org.pale.stumpy2.model.ComponentTypeRegistry;
import org.pale.stumpy2.model.ConnectionType;
import org.pale.stumpy2.model.Parameter;
import org.pale.stumpy2.model.ProtocolException;
import org.pale.stumpy2.model.UnknownComponentTypeException;
import org.pale.stumpy2.model.paramtypes.BoolParam;
import org.pale.stumpy2.model.paramtypes.EnumParam;
import org.pale.stumpy2.model.paramtypes.FloatParam;
import org.pale.stumpy2.model.paramtypes.IntParam;

/**
 * This class contains static methods setting up the configuration, typically
 * creating new value and component types. 
 * @author white
 *
 */
public class Configuration {

	static {

		// create the value types
		ConnectionType.create("flow",'f', Color.BLACK);
		ConnectionType.create("float", 'n', Color.BLUE);
	}

	/// this is a synchronous chat with the server to load the initial
	/// configuration data
	public static void readConfiguration(Client c) throws UnknownComponentTypeException, IOException, ProtocolException{
		c.lock();
		c.doSend("startcomps");
		boolean compsDone = false;

		while(!compsDone){
			CommsResult r = c.syncRead();
			switch(r.code){
			case 410: // new component
				String bits[] = r.status.split(":",7);
				String name = bits[0];
				String inputs = bits[1];
				String outputs = bits[2];
				int paramct = Integer.parseInt(bits[3]);
				String category = bits[4];
				int width = Integer.parseInt(bits[5]);
				int height = Integer.parseInt(bits[6]);
				System.out.println("Component:"+name+" Inputs:"+inputs+
						" Outputs:"+outputs+" ParamCount:"+paramct);
				ComponentType ct = new ComponentType(name,category,width,height);
				// create the inputs
				for(int i=0;i<inputs.length();i++){
					char cc = inputs.charAt(i);
					if(cc=='i')break;
					c.doSend("compinnm "+i);
					CommsResult pr = c.syncRead();
					if(pr.code!=414)
						throw new ProtocolException("Unexpected message "+pr.code);
					ConnectionType contype = ConnectionType.get(cc);
					ct.addInput(contype, pr.status);
				}
				// and the outputs
				for(int i=0;i<outputs.length();i++){
					char cc = outputs.charAt(i);
					if(cc=='i')break;
					c.doSend("compoutnm "+i);
					CommsResult pr = c.syncRead();
					if(pr.code!=415)
						throw new ProtocolException("Unexpected message "+pr.code);
					ConnectionType contype = ConnectionType.get(cc);
					ct.addOutput(contype, pr.status);
				}
				// get the params
				for(int i=0;i<paramct;i++){
					c.doSend("compparam "+i);
					CommsResult pr = c.syncRead();
					if(pr.code != 412)
						throw new ProtocolException("Unexpected message "+pr.code);
					System.out.println("Param "+i+" desc:"+pr.status);

					Parameter p = createParamFromDesc(c,i,pr.status);
					ct.addParameter(p);
				}
				ct.layout();
				ComponentTypeRegistry.getInstance().add(ct);

				c.doSend("nextcomp");		
				break;
			case 411:
				System.out.println("No more components");
				compsDone=true;
				break;
			default:
				throw new ProtocolException("Unexpected message "+r.code);
			}
			System.out.println("component read done");
		}
		c.unlock();
	}
	
	private static String[] readEnumStrings(Client c,int pidx,int ct) throws IOException, ProtocolException{
		LinkedList<String> list = new LinkedList<String>();
		
		for(int i=0;i<ct;i++){
			c.doSend("compenum "+pidx+" "+i);
			CommsResult r = c.syncRead();
			if(r.code==413)
				list.add(r.status);
			else
				throw new ProtocolException("unexpected message in enumeration "+r.code);
		}
		
		return list.toArray(new String[list.size()]);
	}

	private static Parameter createParamFromDesc(Client c,int pidx,String status) throws ProtocolException, NumberFormatException, IOException {
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
			String[] enumStrings = readEnumStrings(c,pidx,Integer.parseInt(s[2]));
			p = new EnumParam(s[1],enumStrings,Integer.parseInt(s[3]));
			break; // Hm.
		default:
			throw new ProtocolException("bad parameter type: "+s[0]);
		}
		return p;
	}


}
