/*
 * UARTConnection.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTCONNECTION_H_
#define UARTCONNECTION_H_

#include <boost/asio/serial_port.hpp>
#include "debug.h"

namespace freejtag {


class UARTConnection {
public:
	UARTConnection(boost::asio::io_service& io_service);
	virtual ~UARTConnection();

	template<typename SettableSerialPortOption>
	bool set_settings(const SettableSerialPortOption& opt);

	bool open(std::string device);
	void close();
private:
	boost::asio::io_service& io_service_;
	boost::asio::serial_port port_;
};

template<typename SettableSerialPortOption>
bool UARTConnection::set_settings(const SettableSerialPortOption& opt) {
	port_.set_option(opt);
	//port_.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even));
	//TODO: catch errors
	//PRINT(port_);
	return true;
}

} /* namespace freejtag */
#endif /* UARTCONNECTION_H_ */
