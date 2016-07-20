package org.pale.stumpy2.libraryview;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;


import org.pale.stumpy2.TopController;
import org.pale.stumpy2.client.Client;
import org.pale.stumpy2.model.ConnectionOutOfRangeException;
import org.pale.stumpy2.model.ConnectionTypeMismatchException;
import org.pale.stumpy2.model.MementoizationException;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.Patch.Memento;
import org.pale.stumpy2.model.PatchLibrary;
import org.pale.stumpy2.model.ProtocolException;
import org.pale.stumpy2.model.UnknownComponentTypeException;
import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.Controller.Command;

/**
 * This is the controller associated with the patch library view.
 * @author white
 *
 */
public class LibraryViewController extends Controller {

    private static Memento clipBoard;
    private PatchLibrary library;
    private LibraryView view;
    

    /**
     * Set the current clipboard. This is a static, so we only have one clipboard.
     * @param clip
     */
    public static void setClipboard(Patch.Memento clip){
        clipBoard = clip;
    }
    
    /**
     * A special ControllerCommand which checks that there is a selected patch.
     * @author white
     *
     */
    abstract class CommandFactoryCheckSelected extends CommandFactory {

        @Override
        public boolean enabled() {
            return view!=null && view.getSelectedPatch()!=null;
        }
    }

    /**
     * A special ControllerCommand which checks that there is a library.
     * @author white
     *
     */
    abstract class CommandFactoryCheckLib extends CommandFactory {

        @Override
        public boolean enabled() {
            return view!=null;
        }
    }

    public void setView(LibraryView v){
    	view=v;
    	library=(view==null)?null:v.getLibrary();
    }
    
    // return the current library
    public PatchLibrary getLibrary(){
    	return library;
    }
    
    public static void createInstance(){
    	instance = new LibraryViewController(TopController.getInstance());
    }
    
    public static LibraryViewController getInstance(){
    	return instance;
    }
    static LibraryViewController instance;

    /**
     * Constructor
     * @param fallback the fallback controller which may provide extra commands if this one doesn't
     */
    private LibraryViewController(Controller fallback) {
        super("libview", null, fallback);


        add("newpatch", new CommandFactoryCheckLib() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        Patch p = new Patch();
                        library.addPatch(p);
                       	view.getContentPane().invalidate();
                        view.getContentPane().repaint();
                    }
                };
            }
        });
        
        add("copy",new CommandFactoryCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        try{
                            setClipboard(view.getMementoForSelectedPatch());
                        } catch(MementoizationException e) {
                            showError("cannot save clip: "+e.getError());
                        }
                    }
                };
            }
        });
        
        add("cut",new CommandFactoryCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        try{
                            setClipboard(view.getMementoForSelectedPatch());
                            Patch p = view.getSelectedPatch();
                            if(p!=null){
                                library.removePatch(p);
                            }
                        } catch(MementoizationException e) {
                            showError("cannot save clip: "+e.getError());
                        }                
                    }
                };
            }
        });
        
        add("paste", new CommandFactory() {
            @Override
            public boolean enabled() { // can only paste when there's something in the clip
                return clipBoard!=null;
            }

            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        if(clipBoard!=null){
                            try {
                                Patch p = new Patch(clipBoard);
                                library.addPatch(p);
                            } catch (UnknownComponentTypeException e) {
                                showError("Paste failed: Unknown component type "+e.getTypeName());
                            } catch (ConnectionOutOfRangeException e) {
                                showError("Paste failed: connection index out of range somewhere");
                            } catch (ConnectionTypeMismatchException e) {
                                showError("Paste failed: connection type mismatch");
                            }
                        }
                    }
                };
            }
        });

        add("save", new CommandFactoryCheckLib() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        try {
                            if (library.save() == false) { // didn't have a name
                                JFileChooser fc = new JFileChooser();
                                File workingDirectory = new File(System.getProperty("user.dir"));
                                fc.setCurrentDirectory(workingDirectory);
                                fc.setFileFilter(new LibraryFileFilter());
                                fc.setAcceptAllFileFilterUsed(false);
                                int rv = fc.showSaveDialog(null);
                                if(rv == JFileChooser.APPROVE_OPTION){
                                    File file = fc.getSelectedFile();
                                    String f = LibraryFileFilter.appendExtensionIfRequired(file).getPath();
                                    library.saveAs(f);
                                }
                                view.setTitleText(library.getFileName());
                            }
                        } catch (FileNotFoundException e) {
                            showError("cannot save : file not found");
                        } catch (MementoizationException e) {
                            showError("error in saving: "+e.getError());
                        }
                    }
                };
            }
        });
        
        add("setactive", new CommandFactoryCheckSelected() {
			
			@Override
			public Command create() {
				return new Command(false) {
					public void execute() {
						library.setActivePatch(view.getSelectedPatch());
						view.redraw();
					}
				};
			}
			public boolean enabled(){
				return library!=null && view!=null && view.getSelectedPatch()!=null;
			}
		});
			
        
        add("rename", new CommandFactoryCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        Patch p = view.getSelectedPatch();
                        if(p!=null){
                            String s = (String) JOptionPane.showInputDialog(
                                    null, "Enter the new name",
                                    "Rename", JOptionPane.PLAIN_MESSAGE, null, null,
                                    p.getName());

                            // If a string was returned, say so.
                            if ((s != null) && (s.length() > 0)) {
                                p.setName(s);
                            }
                        }
                    }
                };
            }
        });
        
        add("sync", new CommandFactoryCheckLib() {
            @Override
            public Command create() {
                return new Command(false) {                    
                    @Override
                    public void execute() {
                        if (!Client.isConnected()) {
                            showError("client is not connected");
                        } else {
                            try {
								library.sync();
							} catch (ProtocolException e) {
								showError("Protocol problem: "+e.toString());

							} catch (IOException e) {
								showError("IO exception: "+e.toString());
							}
                        }
                    }
                };
            }
            @Override
            public boolean enabled(){
                return Client.isConnected();
            }
        });
        
        add("delete", new CommandFactoryCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {                    
                    @Override
                    public void execute() {
                        Patch p = view.getSelectedPatch();
                        if (p != null) {
                            if (JOptionPane.showConfirmDialog(
                                    null,
                                    "Are you sure you want to delete this patch?",
                                    "Confirm", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
                                boolean doIt=false;
                                if(p.hasOpenViews()){
                                    if (JOptionPane.showConfirmDialog(
                                            null,
                                            "That patch has open views! Are you absolutely sure?",
                                            "Confirm", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
                                        doIt = true;
                                    }
                                } else {
                                    doIt = true;
                                }
                                if(doIt){
                                    library.removePatch(p);
                                    p.closeAllViews();
                                }
                            }
                        }
                    }
                };
            }
        });
    }

}
