/*
 * UARTConnection.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#include "UARTConnection.h"

namespace freejtag {

UARTConnection::UARTConnection(boost::asio::io_service& io_service):io_service_(io_service),port_(io_service_) {
	// TODO Auto-generated constructor stub

}

UARTConnection::~UARTConnection() {
	// TODO Auto-generated destructor stub
}

bool UARTConnection::open(std::string device){
	port_.open(device);
	//TODO: Catch errors
	return true;
}

void UARTConnection::close() {
	port_.close();
}

} /* namespace freejtag */
