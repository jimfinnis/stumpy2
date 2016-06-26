package org.pale.stumpy2.ui.support;

import javax.swing.Icon;
import javax.swing.ImageIcon;

public class Images {
	public static Icon createImageIcon(String name){
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
}
