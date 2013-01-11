/*
 * Connection.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#include "Connection.h"
#include "Message.h"
#include "ConnectionException.h"
#include "debug.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
namespace asio = boost::asio;

namespace freejtag {

/**
 * Create a new Connection and bind it to a socket.
 * @param service
 */
Connection::Connection(MessageDatagramQueue& output_queue, asio::io_service& service):cur_message_(Message::createMessage()),
		BaseConnection(service),
		output_queue_(output_queue) {
	PRINT("new Connection");
	;// TODO Auto-generated constructor stub

}

/**
 * Deliver message to this connection.
 * @param msg
 */
void Connection::deliver(const Message::pointer msg) {
	PRINT("Deliver to Client");
	send_mutex_.lock();
	asio::async_write(this->get_socket(),msg->toBuffers(),boost::bind(&Connection::handle_write,
			shared_from_this(),
			asio::placeholders::error,
			asio::placeholders::bytes_transferred,
			msg));
}

/**
 * Create new Connection with a socket on service and return a boost::shared_ptr
 * @param service
 * @return boost::shared_ptr
 */
Connection::pointer Connection::create_new(MessageDatagramQueue& input_messages,boost::asio::io_service& service){
	return pointer(new Connection(input_messages, service));
}

/**
 * What to do after we finished writing to the client.
 * @param err error code
 * @param bytes amount of bytes written
 */
void Connection::handle_write(const boost::system::system_error& err, size_t bytes, const Message::pointer msg){
	if(err.code()){
		throw connection_exception() << connection_info(shared_from_this());
	}
	send_mutex_.unlock();
 	PRINT("Message(" << (int)Message::TypeToInt(msg->getType()) << "," << (int)msg->getLength() << "," << (long)msg->getTimestamp() << ") <== " << bytes << " Byte gesendet an " << socket_.remote_endpoint().address().to_string());
}

Connection::~Connection() {
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
	const Message::pointer msg = Message::createMessage(MESS,"Hello there!");
	buffers.push_back(asio::buffer(&data,1));
	buffers.push_back(asio::buffer(&b,4));
	buffers.push_back(asio::buffer("zweiter"));
	buffers.push_back(asio::buffer("zweiter"));
	asio::async_write(this->get_socket(),msg->toBuffers(),
			boost::bind(&Connection::handle_write,
					shared_from_this(),
					asio::placeholders::error,
					asio::placeholders::bytes_transferred,
					msg));

}

} /* namespace freejtag */
