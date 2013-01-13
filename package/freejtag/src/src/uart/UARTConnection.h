/*
 * UARTConnection.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTCONNECTION_H_
#define UARTCONNECTION_H_

#include <boost/asio/serial_port.hpp>
#include "UARTServiceTypedef.h"
#include "debug.h"

namespace freejtag {

class UARTConnection {
public:
	UARTConnection(boost::asio::io_service& io_service, UARTBuffer& buffer);
	virtual ~UARTConnection();

	template<typename SettableSerialPortOption>
	bool set_settings(const SettableSerialPortOption& opt, std::string name);

	boost::asio::serial_port& get_port();
	bool open(std::string device);
	void close();
private:
	UARTBuffer& buffer_;
	boost::asio::io_service& io_service_;
	boost::asio::serial_port port_;
};

} /* namespace freejtag */
#endif /* UARTCONNECTION_H_ */
