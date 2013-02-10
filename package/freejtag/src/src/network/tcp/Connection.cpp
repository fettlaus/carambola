/*
 * Connection.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#include "Connection.h"

#include "ConnectionException.h"

#include <network/Message.h>
#include <debug.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
namespace asio = boost::asio;

namespace freejtag {

/**
 * Create a new Connection and bind it to a socket.
 * @param service
 */
Connection::Connection(NetworkBuffer& output_queue, asio::io_service& service) :
    cur_message_(Message::create_message()),
    BaseConnection(service),
    output_queue_(output_queue),
    strand_(service){
    PRINT("new Connection");
}

/**
 * Deliver message to this connection.
 * @param msg
 */
void Connection::deliver(const Message::pointer msg) {
    PRINT("Deliver to Client");
    asio::async_write(this->get_socket(), msg->to_buffers(),
        strand_.wrap(boost::bind(&Connection::handle_write, shared_from_this(), asio::placeholders::error,
            asio::placeholders::bytes_transferred, msg)));
}

/**
 * Create new Connection with a socket on service and return a boost::shared_ptr
 * @param service
 * @return boost::shared_ptr
 */
Connection::pointer Connection::create_new(NetworkBuffer& input_messages, boost::asio::io_service& service) {
    return pointer(new Connection(input_messages, service));
}

/**
 * What to do after we finished writing to the client.
 * @param err error code
 * @param bytes amount of bytes written
 * @throw connectionException If an error occurred during writing
 */
void Connection::handle_write(const boost::system::system_error& err, size_t bytes, const Message::pointer msg) {
	if (err.code()) {
        throw connection_exception() << connection_info(shared_from_this());
    }
    PRINT(msg << " <== " << bytes << " Byte gesendet an " << socket_.remote_endpoint().address().to_string());
}

Connection::~Connection() {
}

/**
 *  After receiving the header of a Message, this function starts decoding the Message and decides if we should
 *  read any body or if we can push the Massage as-is to the receiving queue and start listening for the next header.
 * @param err Error while reading header
 * @throw connection_exception If an error occurred during reading
 */
void Connection::handle_read_header(const boost::system::system_error& err) {
    if (err.code()) {
        throw connection_exception() << connection_info(shared_from_this());
    }
    int length = cur_message_->decode_header();
    if (length > 0) {
        boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_body(), length),
            strand_.wrap(boost::bind(&Connection::handle_read_body, shared_from_this(), boost::asio::placeholders::error)));
    } else if (length == 0) {
        PRINT(cur_message_ << "received");
        output_queue_.push(std::make_pair(shared_from_this(), cur_message_));
        cur_message_ = Message::create_message();
        boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
            strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));
    } else {
        WARNING("Header decoding error!");
    }

}

/**
 * After receiving a full Message with body, this function pushes the message to the receiving queue, creates an empty
 *  message and reads a new header into it.
 * @param err Error while reading body
 * @throw connection_exception If an error occurred during reading
 */
void Connection::handle_read_body(const boost::system::system_error& err) {
    if (err.code()) {
        throw connection_exception() << connection_info(shared_from_this());
    }
    PRINT(cur_message_ << "received");
    output_queue_.push(std::make_pair(shared_from_this(), cur_message_));
    cur_message_ = Message::create_message();
    boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
        strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));

}

/**
 * Start the Connection. Has to be called after acquiring a connection or we won't be able to handle input and output.
 */
void Connection::start() {
    boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
        strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));
    /*
     const Message::pointer msg = Message::create_message(MESS,"Hello there!");
     asio::async_write(this->get_socket(),msg->to_buffers(),
     boost::bind(&Connection::handle_write,
     shared_from_this(),
     asio::placeholders::error,
     asio::placeholders::bytes_transferred,
     msg));
     */

}

} /* namespace freejtag */
