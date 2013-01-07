/*
 * Connection.h
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Message.h"

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/ip/tcp.hpp>

//class boost::asio::io_service;
namespace freejtag {

class Message;


class Connection: public boost::enable_shared_from_this<Connection>{
private:
	Connection(boost::asio::io_service& service); ///< Hidden constructor
	boost::asio::ip::tcp::socket socket_; ///< Our socket
	Message cur_message_; ///< The message we are reading into
	void handle_write(const boost::system::error_code& err, size_t);
public:
	typedef boost::shared_ptr<Connection> pointer; ///< Shared pointer to a Connection

	void deliver(const Message&);
	void start();
	static pointer create_new(boost::asio::io_service& service);
	boost::asio::ip::tcp::socket& get_socket();
	//bool send(const Message& msg);
	//void connect_bindings();

};

} /* namespace freejtag */
#endif /* CONNECTION_H_ */
