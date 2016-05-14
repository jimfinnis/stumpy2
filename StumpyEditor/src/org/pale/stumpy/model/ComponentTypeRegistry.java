package org.pale.stumpy.model;

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
     * Add a type object to the map
     * @param t type object to add
     */
    private void add(ComponentType t){
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
    
    /**
     * Use the reflection API to auto-register all components
     * @throws IOException 
     * @throws ClassNotFoundException 
     * @throws NoSuchMethodException 
     * @throws SecurityException 
     * @throws IllegalAccessException 
     * @throws InstantiationException 
     */
    
    public void autoRegister() throws ClassNotFoundException, IOException, SecurityException, NoSuchMethodException, InstantiationException, IllegalAccessException{
        Class cs[] = getClasses("org.pale.stumpy.components");
        
        for(Class c: cs){
            System.out.print("Creating and registering ");
            System.out.println(c.getName());
            
            add((ComponentType)c.newInstance());
        }
    }
    
    
    /**
     * Scans all classes accessible from the context class loader which belong to the given package and subpackages.
     *
     * @param packageName The base package
     * @return The classes
     * @throws ClassNotFoundException
     * @throws IOException
     */
    private static Class[] getClasses(String packageName)
            throws ClassNotFoundException, IOException {
        ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
        assert classLoader != null;
        String path = packageName.replace('.', '/');
        Enumeration<URL> resources = classLoader.getResources(path);
        List<File> dirs = new ArrayList<File>();
        while (resources.hasMoreElements()) {
            URL resource = resources.nextElement();
            dirs.add(new File(resource.getFile()));
        }
        ArrayList<Class> classes = new ArrayList<Class>();
        for (File directory : dirs) {
            classes.addAll(findClasses(directory, packageName));
        }
        return classes.toArray(new Class[classes.size()]);
    }

    /**
     * Recursive method used to find all classes in a given directory and subdirs.
     *
     * @param directory   The base directory
     * @param packageName The package name for classes found inside the base directory
     * @return The classes
     * @throws ClassNotFoundException
     */
    private static List<Class> findClasses(File directory, String packageName) throws ClassNotFoundException {
        List<Class> classes = new ArrayList<Class>();
        if (!directory.exists()) {
            return classes;
        }
        File[] files = directory.listFiles();
        for (File file : files) {
            if (file.isDirectory()) {
                assert !file.getName().contains(".");
                classes.addAll(findClasses(file, packageName + "." + file.getName()));
            } else if (file.getName().endsWith(".class")) {
                classes.add(Class.forName(packageName + '.' + file.getName().substring(0, file.getName().length() - 6)));
            }
        }
        return classes;
    }

}
