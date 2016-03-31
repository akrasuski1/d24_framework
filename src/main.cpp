#include "network.h"
#include "connectionUtils.h"
#include "game.h"

#include <iostream>

int main(int argc, char** argv){
	if(argc<3){
		std::cerr<<"Usage: "<<argv[0]<<" host port"<<std::endl;
		return 0;
	}
	Network network;
	if(!network.connect(argv[1], argv[2])){
		std::cerr<<"Unable to connect to server!"<<std::endl;
		return 0;
	}
	std::iostream& net=network.get_iostream();
	if(!login(net)){
		std::cerr<<"Unable to log in!"<<std::endl;
		return 0;
	}
	while(1){
		std::cerr<<"Started a new game."<<std::endl;
		play(net);
	}
}
