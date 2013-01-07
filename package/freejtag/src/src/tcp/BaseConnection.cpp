/*
 * BaseConnection.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#include "BaseConnection.h"

namespace freejtag {

BaseConnection::BaseConnection(boost::asio::io_service& service):socket_(service){}

/**
 * Get socket of this connection.
 * @return socket
 */
boost::asio::ip::tcp::socket& BaseConnection::get_socket() {
	return socket_;
}


} /* namespace freejtag */
