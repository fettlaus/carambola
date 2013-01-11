/*
 * BaseConnection.h
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#ifndef BASECONNECTION_H_
#define BASECONNECTION_H_
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace freejtag {

class BaseConnection {
public:
	BaseConnection(boost::asio::io_service& service); ///< Hidden constructor
	boost::asio::ip::tcp::socket& get_socket();
protected:
	boost::asio::ip::tcp::socket socket_; ///< Our socket
};

} /* namespace freejtag */
#endif /* BASECONNECTION_H_ */
