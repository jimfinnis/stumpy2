package org.pale.stumpy.main;

import javax.swing.JLabel;
import org.pale.stumpy.client.*;
import org.pale.stumpy.client.Client.Status;

/**
 * Label indicating server status
 * @author white
 *
 */
public class ServerStatus extends JLabel implements Client.StatusListener {
    
    ServerStatus(){
        super();
        Client.addStatusListener(this);
        setText("client not connected");
    }
    
    @Override
    public void newStatus(Status s) {
        System.out.println("STATUS CHANGE: "+s.error);
        
        setText(s.error);
        revalidate();
        
    }

}
