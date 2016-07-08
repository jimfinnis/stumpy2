package org.pale.stumpy2.model.paramtypes;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.text.DecimalFormat;

import javax.swing.JPanel;

import org.pale.stumpy2.model.paramtypes.EnvelopeParam.Envelope;

public class EnvelopePanel extends JPanel {
	private Envelope e;

	public EnvelopePanel(Envelope e){
		this.e = e;
	}
	
	@Override
	public Dimension getMinimumSize(){
		return new Dimension(300,200);
	}
	
    static DecimalFormat formatter = new DecimalFormat("###.##");
	
	@Override
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		g.clearRect(0, 0, getWidth(), getHeight());
		
		float maxt = e.times[EnvelopeParam.ENVSIZE-1];
		if(maxt<0.0001)return;
		
		int maxy = getHeight();
		float timescale = getWidth()/(float)maxt;

		g.setColor(Color.RED);
		for(int i=0;i<EnvelopeParam.ENVSIZE;i++){
			float t = e.times[i];
			t *= timescale;
			g.drawLine((int)t, 0, (int)t, maxy);
			g.drawString(formatter.format(e.times[i]), (int)t, 30);
		}
		
		g.setColor(Color.BLUE);
		g.drawLine(0,maxy/2,getWidth(),maxy/2); // zero axis
		
		// implicit first point
		int prevx = 0;
		int prevy = maxy/2;
		
		g.setColor(Color.BLACK);
		for(int i=0;i<EnvelopeParam.ENVSIZE;i++){
			float t = e.times[i];
			float l = e.levels[i];
			t *= timescale;
			l = ((-l)+1.0f)/2.0f;// from [-1,1] to [1,0] (note y-axis inversion)
			l *= (float)maxy;
			
			g.drawLine(prevx, prevy, (int)t, (int)l);
			prevx=(int)t;
			prevy=(int)l;
		}
	}
}
