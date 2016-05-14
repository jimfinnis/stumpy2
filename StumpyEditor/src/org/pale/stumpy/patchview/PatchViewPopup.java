package org.pale.stumpy.patchview;

import java.awt.Point;
import java.awt.event.MouseEvent;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import org.pale.stumpy.model.Component;
import org.pale.stumpy.model.ComponentAndConnection;
import org.pale.stumpy.model.ComponentType;
import org.pale.stumpy.model.ComponentTypeRegistry;
import org.pale.stumpy.model.NoCurrentPatchException;
import org.pale.stumpy.model.Patch;
import org.pale.stumpy.model.UnknownComponentTypeException;
import org.pale.stumpy.ui.Controller;
import org.pale.stumpy.ui.Controller.CommandFactory;
import org.pale.stumpy.ui.Menu;
import org.pale.stumpy.ui.PopupMenu;
import org.pale.stumpy.ui.Controller.Command;

/**
 * This is the popup menu which is used in the patch view. It's largely
 * responsible for adding new components, but can also handle edit and delete
 * messages.
 * 
 * @author white
 * 
 */
public class PatchViewPopup extends PopupMenu {

    Patch patch;
    Controller controller;
    private PatchCanvas canvas;

    /**
     * A factory for doing the "create component" command
     * 
     * @author white
     * 
     */
    class ComponentCreateCommandFactory extends Controller.CommandFactory {
        private String typeName;
        Point point;

        ComponentCreateCommandFactory(String t, Point point) {
            typeName = t;
            this.point = point;
        }

        // create the command object
        @Override
        public Command create() {
            return new Command(false) {
                @Override
                public void execute() {
                    try {
                        patch.addComponent(typeName, point);
                        canvas.repaint();
                    } catch (UnknownComponentTypeException e) {
                        controller.showError("unknown component " + typeName);
                    } catch (NoCurrentPatchException e) {
                        controller.showError("no current patch");
                    }
                }
            };
        }
    }

    /**
     * This creates the "create" submenu, which must be a Menu not a PopupMenu.
     * It traverses the registry to get all the component types, and creates a
     * CommandFactory for creating each one.
     * 
     * @author white
     * 
     */
    class CreateMenu extends Menu {

        public CreateMenu(String menuname, Controller c, Point componentPoint) {
            super(menuname, c);

            Map<String, Menu> categorySubmenus = new HashMap<String, Menu>();

            // iterate the components, building submenus for the categories as
            // we go along
            for (ComponentType t : ComponentTypeRegistry.getInstance()
                    .getComponents()) {
                String name = t.getName();
                String cat = t.getCategory();
                Menu subMenu;
                if (categorySubmenus.get(cat) == null) {
                    // haven't got a submenu for that category, so make one and
                    // add it
                    subMenu = new Menu(cat, c);
                    categorySubmenus.put(cat, subMenu);
                    add(subMenu);
                } else {
                    subMenu = categorySubmenus.get(cat);
                }
                // /aaaand add a command factory to the menu.
                subMenu.addMenuItem(name, new ComponentCreateCommandFactory(
                        name, componentPoint));
            }
        }
    }

    /**
     * Create the popup
     * 
     * @param canvas
     *            the canvas we're using to edit on
     * @param c
     *            the controller we'll use to process our commands (the
     *            PatchViewController)
     * @param p
     *            the patch we're editing
     * @param componentPoint
     *            the point at which the mouse was clicked, converted in to
     *            patch coordinates.
     */
    public PatchViewPopup(PatchCanvas cv, Controller c, Patch p,
            final Point componentPoint) {
        super("ViewPopup", c);
        patch = p;
        controller = getController();
        this.canvas = cv;

        add(new CreateMenu("create", controller, componentPoint));

        // seems a bit wasteful using a command for this, but it's orthogonal..
        addMenuItem("edit", new CommandFactory() {
            @Override
            public Command create() {
                return new Command(false) {
                    @Override
                    public void execute() {
                        Set<Component> set = canvas.getSelected();
                        for (Component c : set)
                            canvas.openComponentView(c);
                    }
                };
            }
        });
    }

}
