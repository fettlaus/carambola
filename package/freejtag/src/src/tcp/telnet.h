/*
 * telnet.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef TELNET_H_
#define TELNET_H_
//#include<gio/gio.h>
#include <boost/asio/ip/tcp.hpp>
//#include <iostream>
#include "Connection.h"
#include "MessageQueue.h"
#include <set>

namespace asio = boost::asio;

namespace freejtag{
class ConnectionBundle{
public:
	virtual ~ConnectionBundle(){}
	virtual bool sendBroadcast(const Message& msg) = 0;

};

typedef std::set<Connection::pointer> ConnectionList;
class telnet:public ConnectionBundle{
private:
	asio::io_service* io_service;
	asio::ip::tcp::acceptor accepto;
	void start_accept();
	void handle_accept(Connection::pointer ptr, const boost::system::error_code& err);
	ConnectionList connections_;
	MessageQueue<Message>& messages_;
public:
	~telnet();
	telnet(MessageQueue<Message>& messages, int port);
	int run();
	bool sendBroadcast(const Message& msg);
};



}





#endif /* TELNET_H_ */
