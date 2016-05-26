package org.pale.stumpy.main;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JFrame;

import org.pale.stumpy.client.Client;
import org.pale.stumpy.libraryview.PatchLibraryFilter;
import org.pale.stumpy.libraryview.PatchLibraryView;
import org.pale.stumpy.model.ConnectionOutOfRangeException;
import org.pale.stumpy.model.ConnectionTypeMismatchException;
import org.pale.stumpy.model.PatchLibrary;
import org.pale.stumpy.model.ProtocolException;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Controller.Command;

/**
 * This is the top level controller, the controller which doesn't have a patch.
 * It handles New, Quit and other such items. It also creates new views.
 * 
 * It's different from other controllers in that it is a singleton,
 * albeit a rather odd one because it needs the main frame so can only be set up from there
 * 
 * @author white
 *
 */
public class TopController extends Controller {
    
    /**
     * The instance
     */
    private static TopController instance;

    /**
     * The main frame creates the controller with this
     */
    public static void createInstance(JFrame f){
        instance = new TopController(f);
    }

    /**
     * get the controller with this
     * @return the instance
     */
    public static TopController getInstance(){
        return instance;
    }

    private PatchLibrary curLibrary;

    /**
     * Private constructor, adds the commands.
     * 
     */
    private TopController(final JFrame f) {
        super(f);
        add("new", new CommandFactory(){
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        PatchLibrary p = new PatchLibrary();
                        new PatchLibraryView(p);
                    }
                };
            }
        });
        
        add("open",new CommandFactory(){
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        String fileName = null;
                        try {
                            
                            JFileChooser fc = new JFileChooser();
                            fc.setFileFilter(new PatchLibraryFilter());
                            fc.setAcceptAllFileFilterUsed(false);
                            int rv = fc.showOpenDialog(f);
                            if(rv == JFileChooser.APPROVE_OPTION){
                                File file = fc.getSelectedFile();
                                fileName = file.getPath();
                                PatchLibrary p = new PatchLibrary(fileName);
                                new PatchLibraryView(p);
                            }
                        } catch (FileNotFoundException e) {
                            showError("Could not open "+fileName);
                        } catch (UnknownComponentTypeException e) {
                            showError("Load failed: Unknown component type "+e.getTypeName());
                        } catch (ConnectionOutOfRangeException e) {
                            showError("Load failed: connection index out of range somewhere");
                        } catch (ConnectionTypeMismatchException e) {
                            showError("Load failed: connection type mismatch");
                        }
                    }
                };
            }
        });
        
        add("quit", new CommandFactory(){
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        System.exit(0);
                    }
                };
            }
        });
        
        add("connect", new CommandFactory(){

            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        Client.create("127.0.0.1", 65111);
                        if (Client.isConnected()) {
                            // sync the current library
                            if(curLibrary!=null){
                                try {
									curLibrary.sync();
								} catch (ProtocolException e) {
									showError("Protocol problem: "+e.toString());

								} catch (IOException e) {
									showError("IO exception: "+e.toString());
								}
                            }
                        }
                    }
                };
            }
            public boolean enabled(){
                return !Client.isConnected();
            }
        });
        
        add("disconnect", new CommandFactory() {
            
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        Client.destroy();
                    }
                };
            }
            public boolean enabled(){
                return Client.isConnected();
            }
        });    
    }
    
    /**
     * Called when we click on a library view, will make the library the current one for syncing.
     * @param library
     */
    public void setCurrentLibrary(PatchLibrary library) {
        curLibrary = library;
    }


}
