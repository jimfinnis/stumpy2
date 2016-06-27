package org.pale.stumpy2.ui.support;

import java.util.HashMap;
import java.util.Map;

import javax.swing.Icon;
import javax.swing.ImageIcon;

public class Images {
	private static Map<String,Icon> map = new HashMap<String,Icon>();
	
	private static Icon loadImageIcon(String name){
		java.net.URL imgURL = Images.class.getClassLoader().getResource("images/"+name+".gif");
		if(imgURL!=null){
			return new ImageIcon(imgURL,"an icon");
		} else {
			imgURL = Images.class.getClassLoader().getResource("images/"+name+".png");
			if(imgURL!=null){
				return new ImageIcon(imgURL,"an icon");
			}
			else
				throw new RuntimeException("can't find image "+name);
		}
	}
	
	public static Icon getImageIcon(String name){
		Icon i;
		if(map.containsKey(name))
			i = map.get(name);
		else {
			i = loadImageIcon(name);
			map.put(name, i);
		}
		return i;
	}
}
