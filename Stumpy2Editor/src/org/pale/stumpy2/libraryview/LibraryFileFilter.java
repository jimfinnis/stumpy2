package org.pale.stumpy2.libraryview;

import java.io.File;
import javax.swing.filechooser.FileFilter;

public class LibraryFileFilter extends FileFilter {
    
    static final String EXTENSION = "plb";

    @Override
    public boolean accept(File f) {
        if(f.isDirectory())
            return true;
        
        String ext = getExtension(f);
        if(ext!=null && ext.equals(EXTENSION))
            return true;
        
        return false;
    }

    @Override
    public String getDescription() {
        return "Patch library files ("+EXTENSION+")";
    }
    
    
    /*
     * Get the extension of a file.
     */  
    public static String getExtension(File f) {
        String ext = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');

        if (i > 0 &&  i < s.length() - 1) {
            ext = s.substring(i+1).toLowerCase();
        }
        return ext;
    }
    
    /**
     * If a file does not end with the appropriate extension, make it do so.
     * @param f
     * @return
     */
    public static File appendExtensionIfRequired(File f){
        if(!EXTENSION.equals(getExtension(f))){
            return new File(f.getPath()+"."+EXTENSION);
        } else
            return f;
    }


}
