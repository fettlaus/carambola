/*
 * telnet.c
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "telnet.h"
#include "Connection.h"
#include "freejtag.h"
//#include "menu.h"
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

//#include <gio/gio.h>
//#include <glib.h>

// new mainloop
// new socketlistener
// attach_callback()
// on new connection:
// 		callback attaches watch and callback
// on server restart command:
// 		change port in cfg
//		close_connections()
//		attach_callback()
// on shutdown:
//		close_connections()
//		stop socketlistener
//		free resources
//
//
namespace freejtag{

	telnet::telnet(MessageQueue<Message>& messages, int port):io_service(new asio::io_service),messages_(messages),accepto(*io_service,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port)){
		PRINT("new telnet");
		;
	}
	int telnet::run(){
		start_accept();
		PRINT("Run Service");
		io_service->run();
		return 0;
	}
	void telnet::start_accept(){
		PRINT("Start accept");
		Connection::pointer new_conn = Connection::create_new(accepto.get_io_service());
		accepto.async_accept(new_conn->get_socket(),boost::bind(&telnet::handle_accept,this,new_conn,asio::placeholders::error));
	}
	void telnet::handle_accept(Connection::pointer ptr, const boost::system::error_code& err){
		PRINT("New Connection!");
		if(!err){
			ptr->start();
		}
		start_accept();
	}

telnet::~telnet() {

}

bool telnet::sendBroadcast(const Message& msg) {
		//std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::send()))
		return true;
	}


}
