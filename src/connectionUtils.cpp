#include "connectionUtils.h"

#include <iostream>

int expectOK(std::iostream& net){
	std::string s;
	net>>s;
	if(s=="OK"){
		return 0;
	}
	else{
		int e;
		std::string msg;
		net>>e;
		getline(net, msg);
		std::cerr<<"Expected OK, instead received: "<<s<<" "<<e<<msg<<std::endl;
		return e;
	}
}

void waitTurn(std::iostream& net){
	net<<"WAIT"<<std::endl;
	expectOK(net);
	std::string dummy;
	net>>dummy; // WAITING
	expectOK(net);
}

bool login(std::iostream& net){
	std::string s;
	net>>s;
	net<<"our_secret_login"<<std::endl;
	net>>s;
	net<<"our_secret_password"<<std::endl;
	return expectOK(net)==0;
}
