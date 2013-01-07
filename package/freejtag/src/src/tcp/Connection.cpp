/*
 * Connection.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#include "Connection.h"
#include "Message.h"
#include "debug.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
namespace asio = boost::asio;

namespace freejtag {

Connection::Connection(asio::io_service& service):socket(service) {
	PRINT("new Connection");
	;// TODO Auto-generated constructor stub

}

void Connection::deliver(const Message& msg) {
	PRINT("Deliver to Client");
	asio::async_write(socket,msg.toBuffers(),boost::bind(&Connection::handle_write,
			shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred));
}

asio::ip::tcp::socket& Connection::get_socket() {
	return socket;
}

void Connection::handle_write(const boost::system::error_code& err, size_t bytes){
 	PRINT(bytes << " Byte gesendet");
}

Connection::pointer Connection::create_new(boost::asio::io_service& service){
	return Connection::pointer(new Connection(service));
}

void Connection::start(){
	//Message *m = new Message(PING,12312);
	//strncpy(m->body(),"Testeingabe",12);
	//m->encode_header();
	std::vector<boost::asio::const_buffer> buffers;
	uint8_t data;
	data = 0xAB;
	uint32_t b;
	b = 123123;
	buffers.push_back(asio::buffer(&data,1));
	buffers.push_back(asio::buffer(&b,4));
	buffers.push_back(asio::buffer("zweiter"));
	buffers.push_back(asio::buffer("zweiter"));
	asio::async_write(socket,asio::buffer("Test"),
			boost::bind(&Connection::handle_write,
					shared_from_this(),
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));

}

} /* namespace freejtag */
