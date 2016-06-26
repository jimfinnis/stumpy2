package org.pale.stumpy.main;

import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import org.pale.stumpy.Configuration;



/**
 * This class runs the whole program, just by creating the MainFrame class.
 * It can also set the look and feel to the OS look and feel if required (by uncommenting a line)
 * @author white
 *
 */
public class Driver {
    /**
     * Set the look and feel to that of the operating system.
     * Not called by default, but can be.
     */
    @SuppressWarnings("unused")
    private static void setLookAndFeel(){
        try {
            // Set look and feel
            UIManager.setLookAndFeel(
                UIManager.getSystemLookAndFeelClassName());
        } 
        catch (UnsupportedLookAndFeelException e) {
           // handle exception
        }
        catch (ClassNotFoundException e) {
           // handle exception
        }
        catch (InstantiationException e) {
           // handle exception
        }
        catch (IllegalAccessException e) {
           // handle exception
        }
    }
    
    /**
     * the main method - initialises configuration data, creates a MainFrame.
     * @param args
     */
    
    public static void main(String[] args){
        
        Configuration.initialise();

        SwingUtilities.invokeLater(new Runnable(){
            
            @Override
            public void run() {
                // uncomment the following line if you want to use the OS look and feel
                // In Ubuntu 12.04, this is not advised because there's a bug in Swing - 
            	// it's picking up the wrong colour for menu bar text.
                //setLookAndFeel();
            	new MainFrame();
            }            
        });
    }
}
