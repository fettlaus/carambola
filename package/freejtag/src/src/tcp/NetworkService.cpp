/*
 * telnet.c
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "NetworkService.h"
#include "Connection.h"
#include "ConnectionException.h"
#include "debug.h"
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

NetworkService::NetworkService(int port):io_service(new asio::io_service),
			accepto(*io_service,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port)),
			thread_(boost::bind(&NetworkService::run, this)),
			dispatch_thread_(boost::bind(&NetworkService::run_dispatch,this)),
			dispatch_broadcast_thread_(boost::bind(&NetworkService::run_dispatch_broadcast,this)),
			shutdown_(false){
		PRINT("new telnet");
	}
	int NetworkService::run(){
		start_accept();
		PRINT("Run Service");
		while(!shutdown_){
			try{
			io_service->run();
			}catch(boost::system::system_error& err){
				PRINT("Disconnected Client!");
			}catch(connection_exception& err){
				if(Connection::pointer const * con=boost::get_error_info<connection_info>(err))
					connection_bundle_.removeConnection(*con);
			}
		}
		return 0;
	}
	void NetworkService::start_accept(){
		PRINT("Start accept");
		//asio::io_service& ios = accepto.get_io_service();
		Connection::pointer new_conn = Connection::create_new(input_buffer_, *io_service);
		accepto.async_accept(new_conn->get_socket(),boost::bind(&NetworkService::handle_accept,this,new_conn,asio::placeholders::error));
	}
	void NetworkService::handle_accept(Connection::pointer ptr, const boost::system::error_code& err){
		PRINT("incoming Connection!");
		if(!err){
			ptr->start();
		}
		connection_bundle_.addConnection(ptr);
		start_accept();
	}

	NetworkService::~NetworkService() {
	delete io_service;
}

int NetworkService::run_dispatch() {
	while(!shutdown_){
		PRINT("Wait for Message");
		MessageDatagram msg = output_buffer_.pop();
		PRINT("Got Message!");
		msg.first->deliver(msg.second);
	}
	return 0;
}

bool NetworkService::sendBroadcast(Message::pointer msg) {
	broadcast_buffer_.push(msg);
	return true;
}

int NetworkService::run_dispatch_broadcast() {
	while(!shutdown_){
		PRINT("Wait for Broadcast");
		Message::pointer msg = broadcast_buffer_.pop();
		PRINT("Got Broadcast!");
		connection_bundle_.sendBroadcast(msg);
	}
	return 0;
}

bool NetworkService::sendMessage(Connection::pointer ptr, Message::pointer msg) {
	output_buffer_.push(std::make_pair(ptr,msg));
	return true;
}

}
