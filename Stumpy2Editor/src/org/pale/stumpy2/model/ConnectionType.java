package org.pale.stumpy2.model;

import java.awt.Color;
import java.util.HashMap;
import java.util.Map;

/**
 * The types of connections - not parameters -  we can have. These are configurable at the application level, so we can reuse
 * the editor for several applications.. They are stored as objects for type safety,
 * but we refer to them by strings. 
 * To create one, call create().
 * 
 * @author white
 *
 */
public class ConnectionType {
    @Override
    public String toString() {
        return name;
    }

    /**
     * The name
     */
    private String name;
    
    /**
     * The ID code character from the server
     */
    private char id;
    
    /**
     * The colour for use in the editor
     */
    Color col;

    /**
     * static map to get from string to value type object. 
     */
    static Map<String,ConnectionType> mapStrToType = new HashMap<String,ConnectionType>();
    /**
     * And another static map to get from char to object.
     */
    static Map<Character,ConnectionType> mapCharToType = new HashMap<Character,ConnectionType>();
    
    /**
     * private constructor, which will also add the object to the map.
     * @param name
     */
    private ConnectionType(String name,char id,Color c){
        this.name = name;
        this.col = c;
        this.id = id;
        mapStrToType.put(name,this);
        mapCharToType.put(id,this);
    }
    
    /**
     * return the ID, used for checking matching connections
     */
    public int getID(){
    	return id;
    }
    
    /**
     * Get the colour for connections of this type
     * @return colour
     */
    public Color getCol(){
        return col;
    }
    

    /**
     * Get value from name
     * @param name the name of the type we're looking for
     * @return the value type object, or null if it doesn't exist.
     */
    static public ConnectionType get(String name){
        ConnectionType t =mapStrToType.get(name);
        if(t==null)
            throw new RuntimeException("value type unknown : "+name);
        return t;
    }
    
    static public ConnectionType get(char id){
        ConnectionType t =mapCharToType.get(id);
        if(t==null)
            throw new RuntimeException("value type unknown, id: "+id);
        return t;
    }
    
    /**
     * Use this to create connection type objects.
     * @param name the name 
     * @param c the colour for rendering connector/connections of this type
     * @return the new object (which you probably won't use here)
     */
    static public ConnectionType create(String name, char id,Color c){
        if(mapStrToType.get(name)!=null)
            throw new RuntimeException("double create of value type : "+name);
        return new ConnectionType(name,id,c);
    }
    
    public static void clear(){
    	mapStrToType.clear();
    	mapCharToType.clear();
    }
    
}
