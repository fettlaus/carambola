/*
 * Connection.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#include "Connection.h"
#include "freejtag.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
namespace asio = boost::asio;

namespace freejtag {

Connection::Connection(asio::io_service& service):socket(service) {
	PRINT("new Connection");
	;// TODO Auto-generated constructor stub

}
asio::ip::tcp::socket& Connection::get_socket(){
	return socket;
}

void Connection::handle_write(const boost::system::error_code& err, size_t bytes){

}
Connection::pointer Connection::create_new(boost::asio::io_service& service){
	return Connection::pointer(new Connection(service));
}
void Connection::start(){
	asio::async_write(socket,asio::buffer(std::string("Welcome!")),
			boost::bind(&Connection::handle_write,
					shared_from_this(),
					asio::placeholders::error,
					asio::placeholders::bytes_transferred));

}

} /* namespace freejtag */
