package org.pale.stumpy2.model;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/** Singleton which stores all the components by name.
 * Procedure for use: get an instance of this, then add items to it by calling add(). Do this in your initialisation.
 * You'll also need to create ValueType objects.
 * 
 * @author white
 *
 */
public class ComponentTypeRegistry {
    
    /**
     * The instance reference - this is a singleton pattern. Only ever one of these.
     */
    private static ComponentTypeRegistry instance;
    /**
     * The map of component type name onto component type objects.
     */
    private Map<String,ComponentType> map = new HashMap<String,ComponentType>();
    
    /**
     * Discard the previous set
     */
    public void clear(){
    	map.clear();
    }
    
    /**
     * Add a type object to the map
     * @param t type object to add
     */
    public void add(ComponentType t){
        map.put(t.getName(), t);
    }
    
    /** private constructor - this is a singleton! 
     */
    public ComponentTypeRegistry(){
    }
    
    /**
     * Get a component type by name
     * @param name
     * @return component type 
     * @throws UnknownComponentTypeException 
     */
    public ComponentType getComponentType(String name) throws UnknownComponentTypeException{
        if(!map.containsKey(name)){
            throw new UnknownComponentTypeException(name);
        }
        return map.get(name);
    }
    
    /**
     * Return a collection of the components I know about
     * @return collection of components
     */
    public Collection<ComponentType> getComponents(){
        return map.values();
    }
    
    /**
     * The instance-getter of the Singleton pattern. Will allocate the instance the first time.
     * @return the same instance always
     */
    public static ComponentTypeRegistry getInstance(){
        if(null == instance){
            instance = new ComponentTypeRegistry();
        }
        return instance;
    }
}
