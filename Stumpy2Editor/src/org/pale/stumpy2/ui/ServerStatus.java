package org.pale.stumpy2.ui;

import javax.swing.JLabel;
import org.pale.stumpy2.client.*;
import org.pale.stumpy2.client.Client.Status;

/**
 * Label indicating server status
 * @author white
 *
 */
@SuppressWarnings("serial")
public class ServerStatus extends JLabel implements Client.StatusListener {
    public ServerStatus(){
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
