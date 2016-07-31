package org.pale.stumpy2;

import javax.swing.JFrame;
import javax.swing.JMenuBar;

import org.pale.stumpy2.componentview.ComponentBoxView;
import org.pale.stumpy2.libraryview.LibraryMenu;
import org.pale.stumpy2.libraryview.LibraryViewController;
import org.pale.stumpy2.patchview.PatchMenu;
import org.pale.stumpy2.patchview.PatchViewController;
import org.pale.stumpy2.ui.ServerStatus;
import org.pale.stumpy2.ui.Toolbar;

import bibliothek.gui.dock.ExpandableToolbarItemStrategy;
import bibliothek.gui.dock.common.CControl;
import bibliothek.gui.dock.common.CLocation;
import bibliothek.gui.dock.common.layout.RequestDimension;
import bibliothek.gui.dock.toolbar.CToolbarContentArea;
import bibliothek.gui.dock.toolbar.CToolbarItem;
import bibliothek.gui.dock.toolbar.expand.DefaultExpandableToolbarItemStrategy;
import bibliothek.gui.dock.toolbar.location.CToolbarAreaLocation;

public class Main {
	
	private static CControl control=null;
	private static ServerStatus status;
	
	public static CControl getControl(){
		return control;
	}
	
	public static void main(String[] args){
		
		final JFrame frame = new JFrame(); // our all-encompassing main frame
		frame.setTitle("VIOLET PHEASANT");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		control = new CControl(frame);
		control.putProperty( ExpandableToolbarItemStrategy.STRATEGY, new DefaultExpandableToolbarItemStrategy() );

		// now create controllers - top one must be first, as its the fallback for the others
		TopController.createInstance(frame);
		LibraryViewController.createInstance();
		PatchViewController.createInstance();

		// there's only one component pane
		ComponentBoxView.createInstance();

		// and the menus
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		menuBar.add(new FileMenu(TopController.getInstance()));
		menuBar.add(new LibraryMenu(LibraryViewController.getInstance()));
		menuBar.add(new PatchMenu(PatchViewController.getInstance()));
		
		/* Instead of a CContentArea we create a CToolbarContentArea. This class adds four CToolbarAreas around
		 * the five CStations that are usually shown by the CContentArea. */
		CToolbarContentArea area = new CToolbarContentArea( control, "base" );
		control.addStationContainer( area );
		/* ... and added to the frame */
		frame.add( area );

		// and the toolbars

		CToolbarAreaLocation loc = area.getNorthToolbar().getStationLocation();
		
		// main toolbar
		Toolbar tb = new Toolbar(control,loc.group(0).toolbar(0, 0),TopController.getInstance());
		tb.add("connect","toolbarButtonGraphics/general/Export16","connect");
		tb.add("disconnect", "toolbarButtonGraphics/general/Stop16", "disconnect");
		tb.add("open","toolbarButtonGraphics/general/Open16","open");
		tb.add("new","toolbarButtonGraphics/general/New16","new");
		tb.add("clear","icons/cross","clear");
		
		// libview toolbar
		tb = new Toolbar(control,loc.group(0).toolbar(0, 1),LibraryViewController.getInstance());
		tb.add("new","toolbarButtonGraphics/general/Add16","newpatch");
		tb.add("save","toolbarButtonGraphics/general/Save16","save");
		tb.add("copy","toolbarButtonGraphics/general/Copy16","copy");
		tb.add("cut","toolbarButtonGraphics/general/Cut16","cut");
		tb.add("paste","toolbarButtonGraphics/general/Paste16","paste");
		tb.add("sync","icons/arrow_up","sync");
		tb.add("setactive","toolbarButtonGraphics/media/Play16","setactive");

		loc = area.getSouthToolbar().getStationLocation();
		status = new ServerStatus();
		CToolbarItem statitem = new CToolbarItem("status");
		statitem.setItem(status);
		
		ComponentBoxView bv = ComponentBoxView.getInstance();
		control.addDockable(bv);
		bv.setLocation(CLocation.base().normalSouth(0.4));
		bv.setResizeRequest(new RequestDimension(300,true),true);
		bv.setResizeLockedHorizontally(true);

		bv.setVisible(true);
		
		control.addDockable(statitem);
		statitem.setLocation(loc.group(0).toolbar(0, 0).item(0));
		statitem.setVisible(true);

		frame.setBounds(40,40,400,400);
		frame.setVisible(true);
	}
}
