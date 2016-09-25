package org.pale.stumpy2.model;

import java.util.EnumSet;
import java.util.Set;

/**
 * Interface for classes which should be informed when a patch changes, such as a view
 * of that patch.
 * 
 * @author white
 *
 */
public interface PatchChangeListener {
    /**
     * The possible changes which can occur
     * @author white
     *
     */
    public enum PatchChangeType {
        /** The name has changed */
        NAME,
        /** A connection has been added */
        LINK,
        /** an input connection has been unlinked */
        UNLINKINPUT,
        /** an output connection has been unlinked (from all the inputs it feeds) */
        UNLINKOUTPUT,
        /** A component has been added  */
        ADD,
        /** A set of components have been removed */
        REMOVESET,
        /** A set of components as been added */
        ADDSET,
        /** a parameter value has changed */
        PARAMETER,
        /** a "run always" value has changed on a component's output : in this
         * case, the "input" value actually contains the number of the output
         * because of how these constructors work. Hackhackhack. */
        RUNALWAYS,
        /**
         * A component has had its "extra text" updated by the server, or perhaps a name change
         * of some kind. Whatever, the component should be redrawn
         */
        COMPONENTBOX,
        /**
         * A "toggle debug" message needs to be sent.
         */
        DEBUG, 
    }

    /**
     * Data about any change made
     * @author white
     *
     */
    public class PatchChange {
        
        /**
         * The nature of the change.
         */
        private PatchChangeType type;
        /**
         * The component which has been added or deleted, or in the case of
         * a disconnection the component whose input or output has been disconnected. In
         * the case of a new connection, the component which has the input. 
         */
        private Component c;
        /**
         * In the case of a new connection, the component which has the output.
         */
        private Component cOut;
        /**
         * In the case of a new connection, the output we are connecting to.
         */
        private int output;
        /**
         * In the case of a new connection or disconnection, the input.
         * In the case of RUNALWAYS, the actual output number. Yes, I know.
         */
        private int input;
        /**
         * If the change is a parameter change, which parameter is it?
         * 
         */
        private Parameter p;
        /**
         * If the change is a bunch of components being removed, this is the set of components
         * 
         */
        private Set<Component> set;
        
        public Set<Component> getSet() {
            return set;
        }

        public Parameter getParameter() {
            return p;
        }

        public PatchChangeType getType() {
            return type;
        }

        public Component getC() {
            return c;
        }

        public Component getCOut() {
            return cOut;
        }

        public int getOutput() {
            return output;
        }

        public int getInput() {
            return input;
        }

        public PatchChange(PatchChangeType t){
            type = t;
        }
        
        public PatchChange(PatchChangeType t, Component c){
            this(t);
            this.c=c;
        }

        public PatchChange(PatchChangeType t, Component c, int input){
            this(t,c);
            this.input = input;
        }

        public PatchChange(PatchChangeType t, Component c, int input, Component cOut, int output){
            this(t,c,input);
            this.cOut = cOut;
            this.output=output;
        }
        
        public PatchChange(PatchChangeType t,Component c,Parameter p){
            this(t,c);
            this.p=p;
        }
    
        public PatchChange(PatchChangeType t,Set<Component> s){
            this(t);
            this.set=s;
        }
    }

    /**
     * Must be implemented - passed in data about the change which
     * has occurred in the patch.
     * @param change
     */
    public void onPatchChange(Patch p, PatchChange change);
}
