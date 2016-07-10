package org.pale.stumpy2.client;

import java.util.LinkedList;

import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.PatchChangeListener;

public class PatchChangeClientUpdater implements PatchChangeListener {

	@Override
	public void onPatchChange(Patch p, PatchChange change) {
		// don't sync if the client is not connected
		if(!Client.isConnected())
			return;
		Client c = Client.getInstance();
		if(!c.isValid())
			return;
		// don't sync if this patch has not been uploaded to the server
		if(!p.isSynced())
			return;

		LinkedList<String> cmds = new LinkedList<String>();

		switch(change.getType()){
		case RUNALWAYS:
			// the input number in the change structure is actually the output - see
			// PatchChange for why.
			change.getC().writeSyncRunAlwaysCommands(cmds, p.getID(), change.getInput());
			break;
		case NAME:
			break; // I think this should do nothing on the server.
		case ADD:
			change.getC().writeSyncCreateCommands(cmds, p.getID());
			break;
		case ADDSET:
			for(Component comp: change.getSet()){
				comp.writeSyncCreateCommands(cmds, p.getID());
				comp.writeSyncParamCommands(cmds, p.getID());
				comp.writeSyncLinkCommands(cmds, p.getID());
			}
			break;
		case LINK:
			cmds.add("lc "+p.getID()+" "+change.getC().getID()+" "+change.getInput()+" "+change.getCOut().getID()+" "+change.getOutput());
			break;
		case REMOVESET:
			for(Component comp: change.getSet()){
				cmds.add("dc "+p.getID()+" "+comp.getID());
			}
			break;
		case PARAMETER:
			change.getParameter().writeSyncCommand(cmds, p.getID(), change.getC().getID());
			break;
		case UNLINKINPUT:
			cmds.add("ui "+p.getID()+" "+change.getC().getID()+" "+change.getInput());
			break;
		case UNLINKOUTPUT:
			cmds.add("uo "+p.getID()+" "+change.getC().getID()+" "+change.getOutput());
			break;
		default:
			break;
		}

		if(cmds.size()!=0){
			c.sendAndProcessResponse(cmds);
		}



	}

}
