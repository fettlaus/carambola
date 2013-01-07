/*
 * telnet.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef TELNET_H_
#define TELNET_H_
#include "Connection.h"
#include "ConnectionBundle.h"
#include "MessageQueue.h"

//#include<gio/gio.h>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
//#include <iostream>
#include <set>


namespace asio = boost::asio;

namespace freejtag{


/**
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_server.cpp
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html
 */
class NetworkService{
private:
	asio::io_service* io_service;
	asio::ip::tcp::acceptor accepto;
	MessageQueue<Message>& messages_;
	bool shutdown_;
	boost::thread thread_;
	boost::thread dispatch_thread_;
	void start_accept();
	void handle_accept(Connection::pointer ptr, const boost::system::error_code& err);
	int run_dispatch();

	ConnectionBundle connection_bundle_;
public:
	~NetworkService();
	NetworkService(MessageQueue<Message>& messages, int port);
	int run();
	bool sendBroadcast(const Message& msg);
};



}





#endif /* TELNET_H_ */
