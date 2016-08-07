package org.pale.stumpy2.model;

import java.awt.Color;
import java.awt.Graphics;

public class ConnectorComponentType extends ComponentType {

	public ConnectorComponentType(String n, String catName, int width,
			int height) {
		super(n, catName, width, height);
	}
	
	   public void draw(Graphics g, boolean selected, Component c) {
	        g.setColor(selected ? Color.GRAY : LIGHT_GREY);
	        g.fillOval(c.rect.x, c.rect.y, c.rect.width, c.rect.height);

	        g.setColor(selected ? Color.RED : Color.BLACK);
	        g.drawOval(c.rect.x, c.rect.y, c.rect.width, c.rect.height);
	        
	        if(c.extraText!=null){
	        	g.drawString(c.extraText, c.rect.x+5, c.rect.y+12);
	        }
	        if(c.getComment()!=null){
	        	g.setColor(Color.BLACK);
	        	g.drawString(c.getComment(), c.rect.x+2,c.rect.y-7);
	        }

	        for (ConnectionInfo i : inputList)
	            i.draw(g, c.rect.x, c.rect.y);
	        for (ConnectionInfo i : outputList)
	            i.draw(g, c.rect.x, c.rect.y);
	    }

}
