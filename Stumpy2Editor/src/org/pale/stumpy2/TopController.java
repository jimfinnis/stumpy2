package org.pale.stumpy2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.JFrame;

import org.pale.stumpy2.client.Client;
import org.pale.stumpy2.libraryview.LibraryFileFilter;
import org.pale.stumpy2.libraryview.LibraryView;
import org.pale.stumpy2.libraryview.LibraryViewController;
import org.pale.stumpy2.model.ConnectionOutOfRangeException;
import org.pale.stumpy2.model.ConnectionTypeMismatchException;
import org.pale.stumpy2.model.PatchLibrary;
import org.pale.stumpy2.model.ProtocolException;
import org.pale.stumpy2.model.UnknownComponentTypeException;
import org.pale.stumpy2.ui.support.Controller;

public class TopController extends Controller {
	
	private static TopController instance;
	public static TopController getInstance(){
		return instance;
	}
	
	public static void createInstance(JFrame f){
		instance = new TopController(f);
	}
	
	private List<PatchLibrary> openLibs = new ArrayList<PatchLibrary>();
	
    /**
     * Private constructor, adds the commands.
     * 
     */
    private TopController(final JFrame f) {
        super("top",f);
        add("new", new CommandFactory(){
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        PatchLibrary p = new PatchLibrary();
                        openLibs.add(p);
                        new LibraryView(p);
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
                            File workingDirectory = new File(System.getProperty("user.dir"));
                            fc.setCurrentDirectory(workingDirectory);
                            fc.setFileFilter(new LibraryFileFilter());
                            fc.setAcceptAllFileFilterUsed(false);
                            int rv = fc.showOpenDialog(f);
                            if(rv == JFileChooser.APPROVE_OPTION){
                                File file = fc.getSelectedFile();
                                fileName = file.getPath();
                                PatchLibrary p = new PatchLibrary(fileName);
                                openLibs.add(p);

                                new LibraryView(p);
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
                        	PatchLibrary lib = LibraryViewController.getInstance().getLibrary();
                            if(lib!=null){
                                try {
                                	lib.sync();
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
        
        add("clear", new CommandFactory(){
        	public Command create(){
        		return new Command(false){
        			public void execute(){
        		    	Client c = Client.getInstance();
        		    	c.sendCmdAndProcessResponse("clear");
        			}
        		};
        	}
        	public boolean enabled()
        	{
        		return Client.isConnected();
        	}
        });
    }
    
    /**
     * Iterate through all components in all libraries, "rehashing" them by reassociating
     * their component types (which may have been reloaded from the server)
     * @throws UnknownComponentTypeException 
     */
    public void rehashLibraries() throws UnknownComponentTypeException{
    	for(PatchLibrary lib: openLibs){
    		lib.rehash();
    	}
    }
}
