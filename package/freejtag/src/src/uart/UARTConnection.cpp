/*
 * UARTConnection.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#include "UARTConnection.h"
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

namespace freejtag {

UARTConnection::UARTConnection(boost::asio::io_service& io_service, UARTBuffer& buffer):
		io_service_(io_service),
		port_(io_service_),
		buffer_(buffer),
		input_stream_(&stream_buffer_){
	// TODO Auto-generated constructor stub

}

UARTConnection::~UARTConnection() {
	// TODO Auto-generated destructor stub
}

bool UARTConnection::open(std::string device){
	port_.open(device);
	//TODO: Catch errors
	boost::asio::async_read_until(port_,stream_buffer_,'\n',
					boost::bind(&UARTConnection::handle_read,
							this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred)
	);
	return true;
}

boost::asio::serial_port& UARTConnection::get_port() {
	return this->port_;
}

void UARTConnection::close() {
	port_.close();
}

void UARTConnection::handle_read(const boost::system::error_code& ec,
		std::size_t size) {
	//timestamp
	if(!ec){
		std::string new_string;
		std::getline(input_stream_,new_string);
		buffer_.push(std::make_pair(0,new_string));
		//start new read
		boost::asio::async_read_until(port_,stream_buffer_,'\n',
				boost::bind(&UARTConnection::handle_read,
						this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)
		);
	}else{
		WARNING("Something went wrong at UART!");
	}
}

} /* namespace freejtag */
