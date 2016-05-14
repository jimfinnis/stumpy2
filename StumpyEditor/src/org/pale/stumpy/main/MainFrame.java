package org.pale.stumpy.main;

import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JFrame;
import javax.swing.JMenuBar;

import org.pale.stumpy.client.Client;
import org.pale.stumpy.ui.ToolbarFrame;

/** The main frame, which probably won't have much in it apart from a menu bar to open views with.
 * 
 * @author white
 *
 */

@SuppressWarnings("serial")
public class MainFrame extends ToolbarFrame implements WindowListener {
    
    /**
     * Constructor - set up the layout, call build() to add components, then pack and make visible.
     * Also creates the top level controller, handling all commands which work at a higher level
     * than individual patches.
     */
    public MainFrame(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        TopController.createInstance(this);
        setController(TopController.getInstance());

        createMenuBar();
        createToolBar();

        setMinimumSize(new Dimension(500,500));
        setTitle("Stumpy 2 Patch Editor");
        
        getContentPane().add(new ServerStatus());
        
        pack();
        setVisible(true);
    }

    /**
     * add items to the tool bar
     */
    private void createToolBar() {
        addButton("toolbarButtonGraphics/general/New16", "Create a new library", "New", "new");
        addButton("toolbarButtonGraphics/general/Export16", "Connect and sync", "Connect", "connect");
        addButton("toolbarButtonGraphics/general/Stop16", "Disconnect", "Disconnect", "disconnect");
        addButton("toolbarButtonGraphics/general/About16", "Test", "Test", "test");
    }

    /**
     * Build the menu bar and add menus to it. Sets the controller to be the top level controller.
     * @return the menu bar
     */
    private void createMenuBar() {
        addMenu(new FileMenu(getController()));
    }

    @Override
    public void windowActivated(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void windowClosed(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void windowClosing(WindowEvent arg0) {
        if(Client.isConnected()){
            Client.destroy();
        }
    }

    @Override
    public void windowDeactivated(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void windowDeiconified(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void windowIconified(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void windowOpened(WindowEvent arg0) {
        // TODO Auto-generated method stub
        
    }
}
