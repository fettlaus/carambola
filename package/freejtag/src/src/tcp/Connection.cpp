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

/**
 * Create a new Connection and bind it to a socket.
 * @param service
 */
Connection::Connection(asio::io_service& service):socket_(service) {
	PRINT("new Connection");
	;// TODO Auto-generated constructor stub

}

/**
 * Deliver message to this connection.
 * @param msg
 */
void Connection::deliver(const Message& msg) {
	PRINT("Deliver to Client");
	asio::async_write(socket_,msg.toBuffers(),boost::bind(&Connection::handle_write,
			shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred));
}

/**
 * Get socket of this connection.
 * @return socket
 */
asio::ip::tcp::socket& Connection::get_socket() {
	return socket_;
}

/**
 * What to do after we finished writing to the client.
 * @param err error code
 * @param bytes amount of bytes written
 */
void Connection::handle_write(const boost::system::error_code& err, size_t bytes){
 	PRINT(bytes << " Byte gesendet");
}

/**
 * Create new Connection with a socket on service and return a boost::shared_ptr
 * @param service
 * @return boost::shared_ptr
 */
Connection::pointer Connection::create_new(boost::asio::io_service& service){
	return Connection::pointer(new Connection(service));
}

/**
 * Start the Connection. Has to be called after acquiring a connection or we won't be able to handle input and output.
 */
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
	asio::async_write(socket_,asio::buffer("Test"),
			boost::bind(&Connection::handle_write,
					shared_from_this(),
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));

}

} /* namespace freejtag */
