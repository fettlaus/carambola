/**
 * @file Connection.cpp
 * @date Dec 24, 2012
 * @author Arne Wischer<Fettlaus@gmail.com>
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
 * Create a new Connection and a new socket. It needs an io_service object used for dispatching
 * and a queue for received Messages.
 * @param service The io_service object used to dispatch the asynchronous handlers
 * @param input_buffer The NetworkBuffer where received messages will be stored
 */
Connection::Connection(NetworkBuffer& input_buffer, asio::io_service& service) :
    cur_message_(Message::create_message()),
    socket_(service),
    input_buffer_(input_buffer),
    strand_(service){
    PRINT("new Connection");
}

/**
 * Deliver a message to this connection.
 * @param msg The Message which should be delivered
 * @pre The socket needs to be connected
 */
void Connection::deliver(const Message::pointer msg) {
    PRINT("Deliver to Client");
    asio::async_write(this->get_socket(), msg->to_buffers(),
        strand_.wrap(boost::bind(&Connection::handle_write, shared_from_this(), asio::placeholders::error,
            asio::placeholders::bytes_transferred, msg)));
}

/**
 * Create new Connection with a socket and return a boost::shared_ptr. After creation the socket
 * needs to be connected by an acceptor.
 * @param service The io_service object used to dispatch the asynchronous handlers.
 * @param input_buffer The NetworkBuffer where received messages will be stored.
 * @return boost::shared_ptr The pointer that should be used to access this connection.
 */
Connection::pointer Connection::create_new(NetworkBuffer& input_buffer, boost::asio::io_service& service) {
    return pointer(new Connection(input_buffer, service));
}

/**
 * Get the internally used Socket of this connection.
 * @return socket The Socket
 */
asio::ip::tcp::socket& Connection::get_socket() {
	return socket_;
}

/**
 * What to do after we finished writing to the client.
 * @param err Error code
 * @param bytes Amount of bytes written
 * @param msg Message which we have written
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
 *  Handle reading of a message header. After receiving the header of a Message, this function starts
 *  decoding the Message and decides if we should read any body or if we can push the Massage as-is to
 *  the receiving queue and start listening for the next header.
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
        input_buffer_.push(std::make_pair(shared_from_this(), cur_message_));
        cur_message_ = Message::create_message();
        boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
            strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));
    } else {
        WARNING("Header decoding error!");
    }

}

/**
 * Handle reading of a message body. After receiving a full Message with body, this function
 * pushes the message to the receiving queue, creates an empty message and reads a new header into it.
 * @param err Error while reading body
 * @throw connection_exception If an error occurred during reading
 */
void Connection::handle_read_body(const boost::system::system_error& err) {
    if (err.code()) {
        throw connection_exception() << connection_info(shared_from_this());
    }
    PRINT(cur_message_ << "received");
    input_buffer_.push(std::make_pair(shared_from_this(), cur_message_));
    cur_message_ = Message::create_message();
    boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
        strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));

}

/**
 * Start the Connection. Has to be called after acquiring a connection or we won't be able to handle input and output.
 * @pre The socket needs to be connected
 */
void Connection::start() {
    socket_.set_option(boost::asio::ip::tcp::no_delay(true));
    boost::asio::async_read(socket_, boost::asio::buffer(cur_message_->get_header(), cur_message_->header_length),
        strand_.wrap(boost::bind(&Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error)));
}

/**
 * Close the Connection. This shuts the socket down for both directions (to close it gracefully)
 * and closes it afterwards. Async operations should also end after these calls.
 * @todo Handle the possible close error and closing of async operations.
 */
void Connection::close() {
     boost::system::error_code shutdown_error, close_error;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, shutdown_error);
    socket_.close(close_error);
}

} /* namespace freejtag */
