#include "visualizerimpl.h"

DrawableRectangle::DrawableRectangle(pos p, size sz, Color c):
	p(p), sz(sz), color(c){}

DrawableCircle::DrawableCircle(pos p, double diameter, Color c):
	p(p), diameter(diameter), color(c){}

DrawableLine::DrawableLine(pos p1, pos p2, Color c):
	p1(p1), p2(p2), color(c){}

void DrawableRectangle::draw(VisualizerImpl& visu){
	pos pp=visu.toWindowPos(p);
	size szz=visu.toWindowSize(sz);
	visu.window.draw_rectangle(int(pp.x-szz.x/2), int(pp.y-szz.y/2),
		   	int(pp.x+szz.x/2), int(pp.y+szz.y/2), color.rgb);
}

void DrawableCircle::draw(VisualizerImpl& visu){
	pos pp=visu.toWindowPos(p);
	size szz=visu.toWindowSize({diameter, diameter});
	visu.window.draw_circle(int(pp.x), int(pp.y),
		   	int(szz.x/2), color.rgb);
}

void DrawableLine::draw(VisualizerImpl& visu){
	pos pp1=visu.toWindowPos(p1);
	pos pp2=visu.toWindowPos(p2);
	visu.window.draw_line(int(pp1.x), int(pp1.y), int(pp2.x), int(pp2.y), color.rgb);
}
