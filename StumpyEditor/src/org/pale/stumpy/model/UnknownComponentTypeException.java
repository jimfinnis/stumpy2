package org.pale.stumpy.model;

/**
 * Exception thrown when the registry is asked for a type which doesn't exist
 * @author white
 *
 */
@SuppressWarnings("serial")
public class UnknownComponentTypeException extends Exception {
    String typeName;
    
    public UnknownComponentTypeException(String tn){
        typeName = tn;
    }
    public String getTypeName(){
        return typeName;
    }
}
