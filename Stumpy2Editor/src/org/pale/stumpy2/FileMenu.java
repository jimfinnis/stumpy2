package org.pale.stumpy2;

import java.awt.event.KeyEvent;
import java.io.File;
import java.util.LinkedList;
import java.util.List;
import java.util.prefs.Preferences;

import javax.swing.JOptionPane;

import org.pale.stumpy2.client.Client;
import org.pale.stumpy2.ui.Menu;
import org.pale.stumpy2.ui.support.Controller;
import org.pale.stumpy2.ui.support.Controller.Command;
import org.pale.stumpy2.ui.support.Controller.CommandFactory;

public class FileMenu extends Menu {
	public FileMenu(Controller c) {
		super("File", c);
		rebuild();
		inst = this;
	}
	
	private static FileMenu inst = null;
	public static FileMenu getInstance(){
		return inst;
	}
	
    /**
     * show an error - most exceptions should be dealt with this way!
     */
    public void showError(String s){
        JOptionPane.showMessageDialog(null, s);
    }

	
	public void rebuild(){
		removeAll();
		addMenuItem("New",KeyEvent.VK_N,"new");
		addMenuItem("Open",KeyEvent.VK_O,"open");
		addMenuItem("Quit",KeyEvent.VK_W,"quit");
		addRecentFiles();
	}

	public class RecentFileOpenCommandFactory extends CommandFactory {
		String file;
		public RecentFileOpenCommandFactory(String fn){
			super();
			this.file = fn;
		}
		@Override
		public Command create() {
			return new Command(false) {
				@Override
				public void execute() {
					TopController.getInstance().openLib(file);
				}
			};
		}
		public boolean enabled(){
			return (new File(file)).exists() && Client.isConnected();
		}
	}

	private List<String> recentFiles = new LinkedList<String>();

	private void addRecentFiles(){
		Preferences p = Preferences.userNodeForPackage(TopController.class);
		String list = p.get("recentfiles.list",null);
		if(list!=null){
			String[] files = list.split(File.pathSeparator);
			int i=1;
			for(String fn: files){
				if(!recentFiles.contains(fn)){
					System.out.println(fn);
					addMenuItem(String.valueOf(i++)+": "+fn,new RecentFileOpenCommandFactory(fn));
					recentFiles.add(fn);
				}
			}
		}
	}

	public void addToRecentList(String fn){
		StringBuilder sb = new StringBuilder(128);
		if(recentFiles.contains(fn)){
			recentFiles.remove(fn);
		}
		recentFiles.add(0,fn);
		for(String f: recentFiles){
			if(sb.length()>0){
				sb.append(File.pathSeparator);
			}
			sb.append(f);
		}
		Preferences p = Preferences.userNodeForPackage(TopController.class);
		p.put("recentfiles.list",sb.toString());
		rebuild();
	}

}
