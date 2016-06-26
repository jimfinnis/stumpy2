package org.pale.stumpy2.ui.support;

/**
 * This exists because CButton (and perhaps other Docking Frames
 * elements) are not Components, and so cannot be directly called with setEnabled()
 * @author white
 *
 */
public interface UIElement {
	void setEnabled(boolean enable);
}
