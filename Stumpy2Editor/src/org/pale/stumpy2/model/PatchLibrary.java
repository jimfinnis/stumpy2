package org.pale.stumpy2.model;

import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.EnumSet;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.AbstractListModel;

import org.pale.stumpy2.client.Client;
import org.pale.stumpy2.client.PatchChangeClientUpdater;
import org.pale.stumpy2.model.Patch.Memento;

/**
 * A library of patches, in which the patches are indexed by both name and number.
 * That is, each patch has a name; and it also has a number which is used primarily
 * in server communications.
 * @author white
 *
 */
public class PatchLibrary implements PatchChangeListener {

    /**
     * 
     * @return a reference to the patch list. DO NOT MODIFY THE LIST DIRECTLY.
     */
    public List<Patch> getPatchList() {
        return patchList;
    }
    
    /**
     * Which patch is active - i.e. which patch should the server run.
     * May be null, if none has been set.
     */
    private Patch activePatch;
    
    
    
    /**
     * The list of patches. CONSIDER THIS READ-ONLY.
     */
    private List<Patch> patchList = new LinkedList<Patch>();
    /**
     * The filename or null if we haven't saved yet
     */
    private String fileName;
    /**
     * A list of things to be informed if this changes
     */
    private List<ChangeListener> listeners = new LinkedList<ChangeListener>();
    
    private static int idcounter=0;
    private int id = idcounter++;
    
    /**
     * Changes to the patch get sent via this object to the server. This is attached
     * to the patch when addPatch() is called.
     */
    private PatchChangeClientUpdater patchChangeUpdater = new PatchChangeClientUpdater();
    
    private Patch getByName(String name){
        for(Patch q : patchList){
            if(q.getName().equals(name)){
                return q;
            }
        }
        return null;
    }
    
    Pattern suffixPattern = Pattern.compile("\\s+\\([0-9]+\\)\\s*");





    /**
     * Add a patch. If there is a patch with the same name, generate a new name which will be unique.
     * @param p
     */
    public void addPatch(Patch p){
        
        Patch q;
        int n=0;
        Matcher matcher = suffixPattern.matcher(p.getName());
        String baseName = matcher.replaceAll("");        
        String candidateName;
        
        for(;;){
            // build name
            if(n==0){
                candidateName = baseName; // initially, the name we already have
            } else {
                // otherwise append something to the base name to try to make it unique, and retry
                StringBuffer sb = new StringBuffer(baseName);
                sb.append(" (");
                sb.append(n);
                sb.append(") ");
                candidateName = sb.toString();
            }
            if(getByName(candidateName)==null){
                break; // there's no patch of that new name, so leave.
            }
            n++;
        }
        p.setName(candidateName);
        
        patchList.add(p);
        p.addPatchChangeListener(this);
        p.addPatchChangeListener(patchChangeUpdater);
        notifyAdd();
    }
    
    /**
     * Remove a patch. ALWAYS USE THIS.
     * @param p
     */
    public void removePatch(Patch p){
        int idx = patchList.indexOf(p);
        p.removePatchChangeListener(this);
        patchList.remove(p);
        notifyRemove(idx);
        
    }

    /**
     * The memento bean for this class
     * @author white
     *
     */
    static public class Memento {
        List<Patch.Memento> patchList;
        int activePatchIndex;

        public int getActivePatchIndex() {
			return activePatchIndex;
		}

		public void setActivePatchIndex(int activePatchIndex) {
			this.activePatchIndex = activePatchIndex;
		}

		public List<Patch.Memento> getPatchList() {
            return patchList;
        }

        public void setPatchList(List<Patch.Memento> patchList) {
            this.patchList = patchList;
        }
    }
    
    /**
     * Create a memento 
     * @return a new library memento
     * @throws MementoizationException
     */
    public Memento createMemento() throws MementoizationException {
        Memento m = new Memento();
        List<Patch.Memento> pm = new LinkedList<Patch.Memento>();
        for(Patch p: patchList){
            pm.add(p.createMemento(null)); // null means use entire patch, not subset
        }
        if(activePatch!=null){
        	m.setActivePatchIndex(patchList.indexOf(activePatch));
        } else
        	m.setActivePatchIndex(-1);
        
        m.setPatchList(pm);
        return m;
    }
    
    /**
     * Rebuild the patch library from a memento (used in loading)
     * @param m
     * @throws UnknownComponentTypeException
     * @throws ConnectionOutOfRangeException
     * @throws ConnectionTypeMismatchException
     */
    public void resetFromMemento(Memento m) throws UnknownComponentTypeException, ConnectionOutOfRangeException, ConnectionTypeMismatchException{
        for(Patch p: patchList)
            p.removePatchChangeListener(this);
        
        patchList.clear();
        
        for(Patch.Memento pm : m.getPatchList()){
        	Patch p = new Patch(pm);
            patchList.add(p);
            p.addPatchChangeListener(this);
            p.addPatchChangeListener(patchChangeUpdater);
        }
        
        if(m.getActivePatchIndex() != -1){
        	setActivePatch(patchList.get(m.getActivePatchIndex()));
        }
    }
    
    /**
     * Constructor for loading a library from a file
     * @param fileName
     * @throws FileNotFoundException
     * @throws UnknownComponentTypeException
     * @throws ConnectionOutOfRangeException
     * @throws ConnectionTypeMismatchException
     */
    public PatchLibrary(String fileName) throws FileNotFoundException, UnknownComponentTypeException, ConnectionOutOfRangeException, ConnectionTypeMismatchException {
        BufferedInputStream s = new BufferedInputStream(new FileInputStream(fileName));
        XMLDecoder e = new XMLDecoder(s);
        Memento m = (Memento) e.readObject();
        e.close();
        
        this.fileName = fileName;
        resetFromMemento(m);
    }

    /**
     * default ctor for a patch library without a filename
     */
    public PatchLibrary() {
    }

    /**
     * Save the patch library. If false is returned, we don't actually have a filename yet - use saveAs() first, or
     * setFileName()
     * @return true if the save started, false if there was no filename
     * @throws MementoizationException 
     * @throws FileNotFoundException 
     */
    public boolean save() throws MementoizationException, FileNotFoundException{
        boolean rv;
        if(fileName == null) {
            rv=false;
        } else {
            BufferedOutputStream s = new BufferedOutputStream(new FileOutputStream(fileName));
            XMLEncoder e = new XMLEncoder(s);
            Memento m = createMemento();
            e.writeObject(m);
            e.close();

            rv=true;
        }
        return rv;
    }
    
    /**
     * Save the patch under a different file name - must be called if save() returns false because no filename
     * was yet assigned.
     * @param fileName
     * @throws FileNotFoundException
     * @throws MementoizationException
     */
    public void saveAs(String n) throws FileNotFoundException, MementoizationException{
        fileName = n;
        save();
    }
    
    /**
     * An interface for things which need to know when the list changes.
     * @author white
     *
     */
    public interface ChangeListener {
        /**
         * Item added at the end of the list
         */
        void onAddItem();
        /**
         * Item n changed
         * @param n
         */
        void onChangeItem(int n);
        /**
         * Item n removed
         * @param n
         */
        void onRemoveItem(int n);
    }

    public void addChangeListener(ChangeListener listener) {
        listeners.add(listener);
    }
    public void removeChangeListener(ChangeListener listener){
        listeners.remove(listener);
    }
    
    /**
     * A patch has been added, tell our listeners
     */
    public void notifyAdd(){
        for(ChangeListener t: listeners)
            t.onAddItem();
    }
    
    /**
     * A patch has been changed, tell our listeners
     * @param n which patch
     */
    public void notifyChange(int n){
        for(ChangeListener t: listeners)
            t.onChangeItem(n);
    }
    
    /**
     * A patch has been removed
     * @param n which patch
     */
    public void notifyRemove(int n){
        for(ChangeListener t: listeners)
            t.onRemoveItem(n);
    }

    public String getFileName() {
        if(fileName!=null){
            return fileName;
        }
        return "(unnamed library "+id+")";
    }

    /**
     * A patch has changed. If the name has changed, we need to tell the view.
     */
    @Override
    public void update(Patch p, PatchChange change) {
        if(change.getType() == PatchChangeType.NAME){
            notifyChange(patchList.indexOf(p));
        }
    }

    /**
     * Append server synchronisation commands to the given list
     * @param cmds
     */
    public void writeSyncCommands(List<String> cmds) {
    	// clear the existing data
        cmds.add("clear");
        // write the patches
        for(Patch p : patchList){
            p.writeSyncCommands(cmds);
        }
        // send a command to make the active patch active
        if(activePatch!=null){
        	activePatch.writeInstantiateCommand(cmds);
        }
    }

    /**
     * Return the active (running) patch or null
     * @return
     */
	public Patch getActivePatch() {
		return activePatch;
	}

	/**
	 * Set the active (running) patch
	 * @param activePatch
	 */
	public void setActivePatch(Patch activePatch) {
		this.activePatch = activePatch;
	}

    public void sync() throws ProtocolException, IOException {
    	Client c = Client.getInstance();
        if(Client.isConnected()){
            List<String> cmds = new LinkedList<String>();
            writeSyncCommands(cmds);
            c.lock();
            c.sendAndProcessResponse(cmds);
            c.unlock();
        }
    }
}
