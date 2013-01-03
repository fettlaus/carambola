/*
 * Connection.h
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "Message.h"

//class boost::asio::io_service;
namespace freejtag {

class Message;


class Connection: public boost::enable_shared_from_this<Connection>{
private:
	// hidden constructor (use create_new)
	Connection(boost::asio::io_service& service);
	boost::asio::ip::tcp::socket socket;
	void handle_write(const boost::system::error_code& err, size_t);
	Message cur_message_;
public:
	void start();
	bool send(const Message& msg);
	typedef boost::shared_ptr<Connection> pointer;
	static pointer create_new(boost::asio::io_service& service);
	boost::asio::ip::tcp::socket& get_socket();
	void connect_bindings();

};

} /* namespace freejtag */
#endif /* CONNECTION_H_ */
