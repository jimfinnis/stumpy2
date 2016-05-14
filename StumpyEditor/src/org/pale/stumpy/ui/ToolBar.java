package org.pale.stumpy.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JToolBar;


/**
 * My version of a toolbar, which uses the ComponentCommandMap and Controller pattern.
 * @author white
 *
 */
public class ToolBar extends JToolBar implements Refreshable {

    /**
     * The button/command pairs, so we can enable/disable them according
     * to whether the controller will accept them
     */
    private ComponentCommandBindings bindings = new ComponentCommandBindings();

    /**
     * Constructor to create a toolbar, given the orientation
     * @param vertical
     */
    public ToolBar(int vertical) {
        super(vertical);
    }
    
    /**
     * Default constructor
     */
    public ToolBar(){
        super();
    }
    
    /**
     * Set the controller for this toolbar
     * @param controller
     */


    public void setController(Controller controller) {
        bindings.setController(controller);
    }

    
    /**
     * Add a button to the toolbar.
     * @param imageName
     * @param toolTipText
     * @param altText
     * @param command
     */
    public void addButton(String imageName, String toolTipText, String altText, String command) {
        // Look for the image.
        String imgLocation = "/res/images/" + imageName + ".gif";
        URL imageURL = getClass().getResource(imgLocation);

        // Create and initialize the button.
        
        JButton button = new JButton();
        button.setToolTipText(toolTipText);
        button.addActionListener(bindings);
        
        // create an entry in our list of button commands and set the
        // enabled property according to whether the listener will accept it
        bindings.add(button, command);

        if (imageURL != null) { // image found
            button.setIcon(new ImageIcon(imageURL, altText));
        } else { // no image found
            button.setText(altText);
            System.err.println("Resource not found: " + imgLocation);
        }

        add(button);
    }

    @Override
    public void refresh() {
        bindings.refresh();
    }

    /**
     * Return the bindings' controller
     * @return
     */
    public Controller getController() {
        return bindings.getController();
    }

}
