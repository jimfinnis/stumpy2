package org.pale.stumpy2.patchview;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.MouseInputListener;

import org.pale.stumpy2.componentview.ComponentBoxView;
import org.pale.stumpy2.model.Component;
import org.pale.stumpy2.model.ComponentAndConnection;
import org.pale.stumpy2.model.ComponentAndConnection.ComponentClickType;
import org.pale.stumpy2.model.ConnectionOutOfRangeException;
import org.pale.stumpy2.model.ConnectionTypeMismatchException;
import org.pale.stumpy2.model.Patch;
import org.pale.stumpy2.model.Visitor;
import org.pale.stumpy2.patchview.commands.DeleteCommand;
import org.pale.stumpy2.ui.PopupMenu;
//import org.pale.stumpy2.componentview.ComponentView;
//import org.pale.stumpy2.patchview.commands.DeleteCommand;

/**
 * This is the scrollable view of the patch - the actual patch editing is done
 * by this view.
 * 
 * @author white
 * 
 */
@SuppressWarnings("serial")
public class PatchCanvas extends JPanel implements MouseInputListener,
MouseWheelListener {

	class PatchKeyListener implements KeyListener {

		@Override
		public void keyPressed(KeyEvent e) {
			switch (e.getKeyCode()) {
			case KeyEvent.VK_DELETE:
				if (selected != null && selected.size() != 0) {
					// create a delete command and feed it into the controller,
					// rather than
					// editing the patch directly. This makes sure undo
					// processing or whatever
					// will run.
					DeleteCommand c = new DeleteCommand(patch, selected);
					try {
						view.getController().handle(c);
						unselectAll();
					} catch (Exception e1) {
						JOptionPane.showMessageDialog(PatchCanvas.this,
								"Delete Error: " + e1.getMessage());
					}

					revalidate();
					repaint();
				}

				break;
			case KeyEvent.VK_HOME:
				changePage(-1);
				break;
			case KeyEvent.VK_END:
				changePage(1);
				break;
			default:
				break;
			}
		}

		@Override
		public void keyReleased(KeyEvent e) {
		}

		@Override
		public void keyTyped(KeyEvent e) {
		}
	}
	
	// change page, taking selected components with us
	private void changePage(int dir){
		if(dir>0 && curpage==9)return;
		if(dir<0 && curpage==0)return;
		curpage+=dir;
		for(Component c: selected){
			c.page = curpage;
		}
		revalidate();repaint();
	}

	/**
	 * A box dragged out for a selection. We're not using Rectangle, because
	 * that has point/size semantics, and corner/corner semantics is a better
	 * fit.
	 * 
	 * @author white
	 * 
	 */
	private class SelectionBox {
		int x1, y1, x2, y2;

		/**
		 * Constructor
		 * 
		 * @param x
		 * @param y
		 * @param x2
		 * @param y2
		 */
		public SelectionBox(int x, int y, int x2, int y2) {
			this.x1 = x;
			this.y1 = y;
			this.x2 = x2;
			this.y2 = y2;
		}

		public Rectangle getRect() {
			int xa, ya, xb, yb;
			if (x1 < x2) {
				xa = x1;
				xb = x2;
			} else {
				xa = x2;
				xb = x1;
			}
			if (y1 < y2) {
				ya = y1;
				yb = y2;
			} else {
				ya = y2;
				yb = y1;
			}
			return new Rectangle(xa, ya, xb - xa, yb - ya);
		}

		public void update(Point ep) {
			x2 = ep.x;
			y2 = ep.y;
		}

		public void draw(Graphics g) {
			Rectangle r = getRect();
			g.drawRect(r.x, r.y, r.width, r.height);
		}

	}

	/**
	 * The patch we're viewing
	 */
	Patch patch;
	/**
	 * the page we're on
	 */
	int curpage;
	/**
	 * The parent view frame (with toolbar, menu etc.)
	 */
	PatchView view;
	/**
	 * A set of which components are selected
	 */
	Set<Component> selected = new HashSet<Component>();

	/**
	 * The current mouse strategy - mouse events are fed to this object which
	 * deals with them accordingly. The strategy changes when the UI mode
	 * changes.
	 */
	MouseStrategy strategy = new SelectMouseStrategy(this);

	/**
	 * Scale for zoom - this might only be used by scrollbars now.
	 */
	double scale = 1;
	/**
	 * The width of the surface over which we scroll
	 */
	double width = 2000;
	/**
	 * The height of the surface over which we scroll
	 */
	double height = 2000;

	/**
	 * Perform zooming
	 * 
	 * @param zoom
	 *            the factor to adjust the scale by
	 * @param p
	 *            the point around which we zoom (CURRENTLY UNUSED) TODO zoom
	 *            centering
	 */
	void scale(boolean zoom, Point p) {
		double factor = zoom ? 1.08 : 1.0 / 1.08;

		height *= factor;
		width *= factor;
		scale *= factor;

		setPreferredSize(new Dimension((int) width, (int) height));

		revalidate();
		repaint();
	}

	/**
	 * Invert the transform on a point - typically a mouse input - to get the
	 * "real" position.
	 * 
	 * @param point
	 * @return inverse transform of point
	 */
	public Point getInverse(Point point) {

		Point2D.Double p = new Point2D.Double(point.getX(), point.getY());
		p.x /= scale;
		p.y /= scale;

		return new Point((int) p.x, (int) p.y);
	}

	/**
	 * Zoom in
	 * 
	 * @param p
	 *            the point around which we zoom
	 */
	void zoomIn(Point p) {
		scale(true, p);
	}

	/**
	 * Zoom out
	 * 
	 * @param p
	 *            the point around which we zoom
	 */
	void zoomOut(Point p) {
		if (view.areScrollbarsVisible()) {
			scale(false, p);
		}
	}

	/**
	 * Constructor
	 * 
	 * @param p
	 *            the patch to edit
	 * @param v
	 *            the parent view
	 */
	PatchCanvas(Patch p, PatchView v) {
		patch = p;
		view = v;

		addMouseListener(this);
		addMouseMotionListener(this);
		addMouseWheelListener(this);
		addKeyListener(new PatchKeyListener());
		setPreferredSize(new Dimension((int) width, (int) height));
	}

	/**
	 * Get the patch being edited
	 * 
	 * @return patch
	 */
	public Patch getPatch() {
		return patch;
	}

	/**
	 * Add a component to the set of selected components
	 * 
	 * @param c
	 */
	public void select(Component c) {
		selected.add(c);
		ComponentBoxView.getInstance().setSelected(c,true);
	}

	/**
	 * Remove a component from the set of selected components
	 * 
	 * @param c
	 */
	public void unselect(Component c) {
		selected.remove(c);
		ComponentBoxView.getInstance().setSelected(c,false);
	}

	/**
	 * @param c
	 * @return true if the given component is selected
	 */
	public boolean isSelected(Component c) {
		return selected.contains(c);
	}

	/**
	 * Return a list of selected items
	 * 
	 * @return
	 */
	public Set<Component> getSelected() {
		return selected;
	}

	/**
	 * Select all components which intersect a given rectangle
	 * 
	 * @param r
	 */
	public void selectWithin(final Rectangle r) {
		patch.visitAll(new Visitor() {
			@Override
			public void visitComponent(Component c) {
				if (c.page==curpage && r.intersects(c.rect))
					select(c);
			}
		});
	}

	/**
	 * Unselect all components which intersect a given rectangle
	 * 
	 * @param r
	 */
	public void unselectWithin(final Rectangle r) {
		patch.visitAll(new Visitor() {
			@Override
			public void visitComponent(Component c) {
				if (c.page==curpage && r.intersects(c.rect))
					unselect(c);
			}
		});
	}

	/**
	 * Unselect all components
	 */
	public void unselectAll() {
		patch.visitAll(new Visitor() {
			@Override
			public void visitComponent(Component c) {
				unselect(c);
			}
		});
		// now, some components may have been deleted so they don't appear
		// in the patch's list, but are still in my selected list. Deal with
		// this just by clearing the selected list to make sure.
		selected.clear();
	}

	/**
	 * Paint the view. Adds the scaling to the graphics object's transform for
	 * zooming, then draws all the components and wiring.
	 * 
	 */
	@Override
	protected void paintComponent(final Graphics g) {
		super.paintComponent(g);

		Graphics2D g2D = (Graphics2D) g;
		
		// without the transform..
		g.setColor(Color.BLACK);
		g.drawString(String.valueOf(curpage), 0,10);

		AffineTransform t = new AffineTransform();
		t.setToScale(scale, scale);
		g2D.transform(t); // this used to say setTransform(). That was WRONG.
		// TWO DAYS this cost me.

		// we visit twice, drawing the connections over the components so they're always visible.
		patch.visitAll(new Visitor() {

			@Override
			public void visitComponent(Component c) {
				if(c.page == curpage)
					c.draw(g, isSelected(c));
			}
		});
		patch.visitAll(new Visitor() {
			@Override
			public void visitComponent(Component c) {
				try {
					c.drawConnections(g, isSelected(c),curpage);
				} catch (ConnectionOutOfRangeException e) {
					view.setStatus("error in draw: connection index out of range!");
				}
			}
		});



		if (isDraggingSelection()) {
			g.setColor(Color.GRAY);
			selectionBox.draw(g);
		}

		if (isRubberbandingConnection()) {
			g.setColor(Color.RED);
			drawRubberband(g);
		}
		g.setColor(Color.BLACK); // reset the colour

		/*
		 * for(int x=0;x<2000;x+=100){ for(int y=0;y<2000;y+=100){
		 * g.drawLine(x-10, y, x+10, y); g.drawLine(x,y-10,x,y+10); String str =
		 * Integer.toString(x)+","+Integer.toString(y); g.drawString(str, x, y);
		 * } }
		 */
		
		
	}

	/**
	 * Draw the current rubber band, getting the coordinates of the appropriate
	 * starting point from the component type object.
	 * 
	 * @param g
	 */
	private void drawRubberband(Graphics g) {
		Point p;
		try {
			p = rubberbandingConnection.getPosition();
			g.setColor(Color.BLACK);
			if (p != null) { // if this is null, we've probably had a connection
				// out of range
				g.drawLine(p.x, p.y, rubberbandEndpoint.x, rubberbandEndpoint.y);
			}
		} catch (ConnectionOutOfRangeException e) {
			view.setStatus("cannot connect: connection index out of range");
			rubberbandingConnection = null;
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// just to make damn sure we have the right view. Ugly.
		PatchViewController.getInstance().setView(view);

		Point p = getInverse(e.getPoint());
		strategy.mouseClicked(e, p, curpage);

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		Point p = getInverse(e.getPoint());
		strategy.mouseEntered(e, p, curpage);

	}

	@Override
	public void mouseExited(MouseEvent e) {
		Point p = getInverse(e.getPoint());
		strategy.mouseExited(e, p, curpage);
	}

	@Override
	public void mousePressed(MouseEvent e) {

		Point p = getInverse(e.getPoint());
		strategy.mousePressed(e, p, curpage);

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		Point p = getInverse(e.getPoint());
		strategy.mouseReleased(e, p, curpage);
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		Point p = getInverse(e.getPoint());
		strategy.mouseDragged(e, p, curpage);
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		Point p = getInverse(e.getPoint());
		strategy.mouseMoved(e, p, curpage);
	}

	/**
	 * The dragging offset (i.e. difference between component top left and drag
	 * start)
	 */
	private Point dragOffset;
	/**
	 * The selection box, if we're dragging a selection box (or null).
	 */
	private SelectionBox selectionBox;

	/**
	 * The data for the connection we're rubberbanding (or null)
	 */
	private ComponentAndConnection rubberbandingConnection;
	/**
	 * The endpoint of the current rubberband if any.
	 */
	private Point rubberbandEndpoint;

	/**
	 * Start dragging the selected components
	 * 
	 * @param c
	 * @param start
	 *            the start of the drag, where the mouse was clicked
	 */
	public void startDragComponent(Component c, Point start) {
		// if the set of selected items doesn't contain c,
		// we're just dragging that item.
		if (!selected.contains(c)) {
			unselectAll();
			select(c);
		}
		dragOffset = new Point(start.x, start.y);
		repaint();

		// stash the original positions
		dragOriginPoints = new HashMap<Component, Point>();
		for (Component cc : selected) {
			Point p = new Point(cc.rect.x, cc.rect.y);
			dragOriginPoints.put(cc, p);
		}
	}

	/**
	 * A map of the original points, before dragging, of each component
	 */
	private Map<Component, Point> dragOriginPoints;

	/**
	 * The user has released the mouse - end the drag of a component
	 */
	public void endDragComponent() {
		dragOffset = null;

	}

	/**
	 * Is the user dragging a component?
	 * 
	 * @return true if a component is being dragged
	 */
	public boolean isDraggingComponent() {
		return dragOffset != null;
	}

	/**
	 * If the user is dragging components, move them accordingly and
	 * repaint.
	 * 
	 * @param point
	 */
	public void handleDragComponent(Point point) {
		if (isDraggingComponent()) {
			int dx = point.x - dragOffset.x;
			int dy = point.y - dragOffset.y;
			for (Component c : selected) {
				Point origin = dragOriginPoints.get(c);
				c.rect.x = origin.x + dx;
				c.rect.y = origin.y + dy;
			}
			repaint();
		}
	}

	/**
	 * Start rubberbanding a selection box
	 * 
	 * @param ep
	 *            the start point
	 */
	public void startDragSelection(Point ep) {
		unselectAll();
		selectionBox = new SelectionBox(ep.x, ep.y, ep.x, ep.y);
		repaint();

	}

	/**
	 * 
	 * @return true if the user is dragging a selection box
	 */
	public boolean isDraggingSelection() {
		return selectionBox != null;
	}

	/**
	 * The user has released the selection box drag, select the contained
	 * components.
	 */
	public void endDraggingSelection() {
		final Rectangle r = selectionBox.getRect();
		patch.visitAll(new Visitor() {
			@Override
			public void visitComponent(Component c) {
				if (r.contains(c.rect))
					select(c);
			}
		});
		repaint();
		selectionBox = null;
	}

	/**
	 * The user is dragging the selection box, update the coordinates
	 * 
	 * @param ep
	 */
	public void handleDragSelection(Point ep) {
		selectionBox.update(ep);
		repaint();
	}

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		Point p = e.getPoint();
		p = getInverse(p);

		int notches = e.getWheelRotation();

		while (notches < 0) {
			zoomIn(p);
			notches++;
		}
		while (notches > 0) {
			zoomOut(p);
			notches--;
		}

	}

	/**
	 * The user has clicked on the input or output of a component, so we're
	 * starting a rubberband. We do NOT clear existing connections, since the
	 * model allows many inputs to be fed from the same output.
	 * 
	 * @param cc
	 *            the ComponentClick associated with the event.
	 */
	public void startConnectionRubberband(ComponentAndConnection cc) {
		unselectAll();
		select(cc.c);
		rubberbandingConnection = cc;
		repaint();
	}

	/**
	 * 
	 * @return true if the user is currently rubberbanding a connection
	 */
	public boolean isRubberbandingConnection() {
		return rubberbandingConnection != null;
	}

	/**
	 * The user has started dragging from an input, so we should delete any
	 * existing connection there.
	 * @param c
	 * @param ep
	 */
	public void breakConnection(ComponentAndConnection cc) {
		try {
			cc.disconnect(patch);
		} catch (ConnectionOutOfRangeException e) {
			view.setStatus("cannot disconnect");
			e.printStackTrace();
		}
	}



	/**
	 * The user has finished dragging the rubberband; try to make a connection
	 * with it
	 * 
	 * @param p
	 */
	public void endConnectionRubberband(Point p) {
		// anything at the endpoint?
		ComponentAndConnection endPoint = patch.getComponentAtPoint(p,curpage);
		if (endPoint != null && isRubberbandingConnection()) {
			// if we came from an input; we need to find an output
			try {
				if (rubberbandingConnection.type == ComponentClickType.INPUT
						&& endPoint.type == ComponentClickType.OUTPUT) {
					patch.setComponentInput(rubberbandingConnection.c,
							rubberbandingConnection.index, endPoint.c,
							endPoint.index);
					view.setStatus("connection OK - ready");
				}
				// if we came from an output; we need to find an input
				else if (rubberbandingConnection.type == ComponentClickType.OUTPUT
						&& endPoint.type == ComponentClickType.INPUT) {
					patch.setComponentInput(endPoint.c, endPoint.index,
							rubberbandingConnection.c,
							rubberbandingConnection.index);
					view.setStatus("connection OK - ready");
				} else
					view.setStatus("ready");
			} catch (ConnectionOutOfRangeException e) {
				view.setStatus("cannot connect - invalid connection index");
			} catch (ConnectionTypeMismatchException e) {
				view.setStatus("cannot connect: input/output type mismatch");
			}

		} else
			view.setStatus("ready");
		rubberbandingConnection = null; // and clear the rubberband.
		repaint();
	}

	/**
	 * The user is dragging the rubberband for a connection, update the
	 * endpoint.
	 * 
	 * @param p
	 */
	public void handleConnectionRubberband(Point p) {
		rubberbandEndpoint = p;
		repaint();
	}

	/* TODO - the component map handling in canvas

	/**
	 * A map, indicating if any views are open for any components. If we attempt
	 * to reopen a view on a component, we'll just pull the existing one to the
	 * front.
	 */
	//	Map<Component, ComponentView> openComponentViews = new HashMap<Component, ComponentView>();

	/**
	 * Open a component view to edit this component - or if one is already open,
	 * focus on it.
	 * 
	 * @param c
	 */
	public void openComponentView(final Component c) {
		ComponentBoxView bv = ComponentBoxView.getInstance();
		bv.add(c);
		/*		ComponentView v = openComponentViews.get(c);
		if (v != null) {
			v.toFront();
		} else {
			v = new ComponentView(patch, c);

			// / here we just add a listener to remove us from the map when
			// we're done.
			v.addWindowListener(new WindowListener() {

				@Override
				public void windowActivated(WindowEvent e) {
				}

				@Override
				public void windowClosed(WindowEvent e) {
					openComponentViews.remove(c);
				}

				@Override
				public void windowClosing(WindowEvent e) {
				}

				@Override
				public void windowDeactivated(WindowEvent e) {
				}

				@Override
				public void windowDeiconified(WindowEvent e) {
				}

				@Override
				public void windowIconified(WindowEvent e) {
				}

				@Override
				public void windowOpened(WindowEvent e) {
				}

			});
			openComponentViews.put(c, v);
		}
		 */	}

	/**
	 * Create the popup menu
	 */
	public void openPopup(MouseEvent e, Point componentPoint) {
		PopupMenu menu = new PatchViewPopup(this, view.getController(), patch,
				componentPoint);

		menu.show(this, e.getX(), e.getY());
	}

}
