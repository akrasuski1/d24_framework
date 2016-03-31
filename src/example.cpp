#include "visualizer.h"
#include <unistd.h>
#include <cmath>

int main(){
	Visualizer visu;
	int blue=0;
	int x=0;
	while(1){
		// Simulating getting updates from server.
		blue+=50;
		blue&=0xFF;
		x++;
		x%=10;
		// Now drawing the situation on visualization.
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				visu.add(std::unique_ptr<DrawableObj>(new 
						DrawableRectangle({double(i),double(j)},{0.9,0.9},{uint8_t(i*j*60),255,uint8_t(blue)})));
			}
		}
		visu.add(std::unique_ptr<DrawableObj>(new 
				DrawableCircle({double(x),2.0},1.0,{255,0,255})));
		visu.add(std::unique_ptr<DrawableObj>(new 
				DrawableLine({2.0,2.0},{3.0,2.0},{255,255,0})));
		visu.flip();
		// We can wait for user input, if wanted.
		usleep(750000);
		// Getting user input (click position and modifiers only, enough for most purposes).
		auto clicks=visu.getClickPos();
		if(clicks.count(MouseFlag::left)){
			pos pp=clicks[MouseFlag::left];
			std::pair<int,int> pii(round(pp.x), round(pp.y));
			printf("Hmm, there's a LMB click at (%lf, %lf) - target square: (%d, %d).\n",
					pp.x, pp.y, pii.first, pii.second);
		}
		// Simulating calculations and sending processed data back to server.
		usleep(250000);
	}

}
