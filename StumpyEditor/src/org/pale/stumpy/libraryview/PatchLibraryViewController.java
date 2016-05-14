package org.pale.stumpy.libraryview;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import org.pale.stumpy.InitialPatch;
import org.pale.stumpy.client.Client;
import org.pale.stumpy.model.ConnectionOutOfRangeException;
import org.pale.stumpy.model.ConnectionTypeMismatchException;
import org.pale.stumpy.model.MementoizationException;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.Patch.Memento;
import org.pale.stumpy.model.PatchLibrary;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Controller.Command;

/**
 * This is the controller associated with the patch library view.
 * @author white
 *
 */
public class PatchLibraryViewController extends Controller {

    private static Memento clipBoard;
    private PatchLibrary library;
    private PatchLibraryView view;
    

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
    abstract class ControllerCommandCheckSelected extends CommandFactory {

        @Override
        public boolean enabled() {
            return view.getSelectedPatch()!=null;
        }

    }

    /**
     * Constructor
     * @param v the view for this controller
     * @param fallback the fallback controller which may provide extra commands if this one doesn't
     * @param lib the library we are controlling
     */
    public PatchLibraryViewController(PatchLibraryView v, Controller fallback,
            PatchLibrary lib) {
        super(v, fallback);
        
        library=lib;
        view = v;

        add("new", new CommandFactory() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        Patch p = new InitialPatch();
                        library.addPatch(p);
                        view.invalidate();
                        view.repaint();
                    }
                };
            }
        });
        
        add("copy",new ControllerCommandCheckSelected() {
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
        
        add("cut",new ControllerCommandCheckSelected() {
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

        add("save", new CommandFactory() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        try {
                            if (library.save() == false) { // didn't have a name
                                JFileChooser fc = new JFileChooser();
                                fc.setFileFilter(new PatchLibraryFilter());
                                fc.setAcceptAllFileFilterUsed(false);
                                int rv = fc.showSaveDialog(view);
                                if(rv == JFileChooser.APPROVE_OPTION){
                                    File file = fc.getSelectedFile();
                                    String f = PatchLibraryFilter.appendExtensionIfRequired(file).getPath();
                                    library.saveAs(f);
                                }
                                view.setTitle(library.getFileName());
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
        
        add("rename", new ControllerCommandCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {
                    
                    @Override
                    public void execute() {
                        Patch p = view.getSelectedPatch();
                        if(p!=null){
                            String s = (String) JOptionPane.showInputDialog(
                                    view, "Enter the new name",
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
        
        add("sync", new CommandFactory() {
            @Override
            public Command create() {
                return new Command(false) {                    
                    @Override
                    public void execute() {
                        if (!Client.isConnected()) {
                            showError("client is not connected");
                        } else {
                            library.sync();
                        }
                    }
                };
            }
            @Override
            public boolean enabled(){
                return Client.isConnected();
            }
        });
        
        add("delete", new ControllerCommandCheckSelected() {
            @Override
            public Command create() {
                return new Command(false) {                    
                    @Override
                    public void execute() {
                        Patch p = view.getSelectedPatch();
                        if (p != null) {
                            if (JOptionPane.showConfirmDialog(
                                    view,
                                    "Are you sure you want to delete this patch?",
                                    "Confirm", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
                                boolean doIt=false;
                                if(p.hasOpenViews()){
                                    if (JOptionPane.showConfirmDialog(
                                            view,
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
