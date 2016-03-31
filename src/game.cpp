#include "game.h"
#include "connectionUtils.h"

#include "visualizer.h"
#include <unistd.h>
#include <cmath>
#include <iostream>

struct ipos{
	int x,y;
};

void play(std::iostream& net){
	Visualizer visu;
	int blue=0;
	int x=0;
	while(1){
		// Simulating getting updates from server.
		net<<"WHATEVER 1 0"<<std::endl;
		expectOK(net);
		std::string s;
		net>>s;
		std::cout<<"Received: "<<s<<std::endl;

		blue+=50;
		blue&=0xFF;
		x++;
		x%=10;
		// Now drawing the situation on visualization.
		for(int i=0;i<200;i++){
			for(int j=0;j<200;j++){
				visu.add(std::unique_ptr<DrawableObj>(new DrawableRectangle(
					{double(i),double(j)}, // Position.
					{0.9,0.9}, // Size - less than 1 to leave black grid.
					{uint8_t(i*j*60),255,uint8_t(blue)} // Color (RGB).
				)));
			}
		}
		visu.add(std::unique_ptr<DrawableObj>(new DrawableCircle(
			{double(x),2.0}, // Position.
			1.0, // Diameter.
			{255,0,255} // Color.
		)));
		visu.add(std::unique_ptr<DrawableObj>(new DrawableLine(
			{2.0,2.0}, // Start position.
			{3.0,2.0}, // End position.
			{255,255,0} // Color.
		)));
		visu.flip();
		// We can wait for a while for user input, if we want to.
		usleep(750000);
		// Getting user input (click position and modifiers only, enough for most purposes).
		auto clicks=visu.getClickPos();
		if(clicks.count(MouseFlag::left)){
			pos pp=clicks[MouseFlag::left];
			ipos pii{int(pp.x+0.5), int(pp.y+0.5)};
			printf("Hmm, there's a LMB click at (%lf, %lf) - target square: (%d, %d).\n",
					pp.x, pp.y, pii.x, pii.y);
			printf("    Let's use this information...\n");
		}

		net<<"HERPDERP"<<std::endl;
		expectOK(net);
		waitTurn(net);
	}

}
