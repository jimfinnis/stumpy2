package org.pale.stumpy.model;

/**
 * Exception for general protocol errors, typically in reading the initial
 * configuration from the server.
 * @author white
 *
 */
@SuppressWarnings("serial")
public class ProtocolException extends Exception {
	String error;
	public ProtocolException(String e){
		error = e;
	}
	public String getError(){
		return error;
	}
}
