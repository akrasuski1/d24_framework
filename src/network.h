#ifndef NETWORK_H_
#define NETWORK_H_

#include <boost/asio.hpp>
#include <memory>

class Network{
public:
	using tcp=boost::asio::ip::tcp;
	bool connect(std::string host, std::string port);
	std::iostream& get_iostream();
private:
	std::unique_ptr<tcp::iostream> connection;
};

#endif
