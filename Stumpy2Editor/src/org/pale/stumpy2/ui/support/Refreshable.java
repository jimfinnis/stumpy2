package org.pale.stumpy2.ui.support;


/**
 * A thing which can be refreshed. Typically a composite UI element, like a toolbar or menu.
 * @author white
 *
 */
public interface Refreshable {
    /**
     * Query all components, resetting their disabled/enabled state according to whether
     * the controller deems the command bound to that component to be acceptable.
     * Typically this should just call refresh() in the bindings object.
     */
    void refresh();
}
