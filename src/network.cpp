#include "network.h"

bool Network::connect(std::string host, std::string port){
	connection=std::unique_ptr<tcp::iostream>(new tcp::iostream(host,port));

	tcp::no_delay opt(true);
	connection->rdbuf()->set_option(opt);

	return connection->good();
}

std::iostream& Network::get_iostream(){
	return *connection;
}
