package org.pale.stumpy.ui;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.net.URL;
import java.util.Collection;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JToolBar;
import javax.swing.border.EmptyBorder;


/**
 * Frame with a toolbar. It must be set a StringListener using setListener(). Buttons which are added
 * to the toolbar will be given a string which will be sent to this listener on click.
 * @author white
 *
 */
@SuppressWarnings("serial")
public class ToolbarFrame extends JFrame implements Refreshable {
    /**
     * The toolbar
     */
    private ToolBar toolBar;
    
    /**
     * The menu bar
     */
    private JMenuBar menuBar;
    
    
    /**
     * Set the string listener for commands. When a button is pressed in the toolbar, the string
     * associated with that button will be sent to this listener.
     * @param controller
     */
    public void setController(Controller c) {
        toolBar.setController(c);
        toolBar.refresh();

        c.addRefreshable(this);
    }
    
    /**
     * Return the toolbar's controller
     * @return
     */
    public Controller getController(){
        return toolBar.getController();
    }

    /**
     * Constructor.
     */

    public ToolbarFrame(){
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        Container p = getContentPane();

        p.setLayout(new BorderLayout(0, 0));

        toolBar = new ToolBar(JToolBar.VERTICAL);       
        p.add(toolBar,BorderLayout.LINE_START);

        menuBar = new JMenuBar();
        setJMenuBar(menuBar);
        
        // make sure this gets removed from the list of things the controller should refresh when it closes
        addWindowListener(new WindowListener() {
            
            @Override
            public void windowOpened(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
            
            @Override
            public void windowIconified(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
            
            @Override
            public void windowDeiconified(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
            
            @Override
            public void windowDeactivated(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
            
            @Override
            public void windowClosing(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
            
            @Override
            public void windowClosed(WindowEvent e) {
                if(getController()!=null)
                    getController().removeRefreshable(ToolbarFrame.this);
            }
            
            @Override
            public void windowActivated(WindowEvent e) {
                // TODO Auto-generated method stub
                
            }
        });
    }
    
    /**
     * Add an item to the toolbar. Delegates to the toolbar.
     * @param imageName the image path within res/images
     * @param toolTipText the tooltip text
     * @param altText the alt text if the image cannot be found
     * @param command the command to run on the controller when the button is pressed
     * 
     */
    public void addButton(String imageName, String toolTipText, String altText, String command) {
        toolBar.addButton(imageName, toolTipText, altText, command);
    }
    
    List<Menu> menus = new LinkedList<Menu>(); 
    
    /**
     * Add a menu to the menu bar
     * 
     */
    public void addMenu(Menu m){
        menuBar.add(m);
    }
    
    /**
     * refresh enabled/disabled state of buttons and menus
     */
    @Override
    public void refresh(){
        toolBar.refresh();
        for(Menu m:menus){
            m.refresh();
        }
    }
}
