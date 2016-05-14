package org.pale.stumpy.model;

/**
 * Thrown when an error occurs during memoisation
 * @author white
 *
 */
public class MementoizationException extends Exception {

    String error;
    public String getError() {
        return error;
    }
    public MementoizationException(String string) {
        error = string;
    }

}
