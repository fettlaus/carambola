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
	bool set_settings(const SettableSerialPortOption& opt, std::string name);

	bool open(std::string device);
	void close();
private:
	boost::asio::io_service& io_service_;
	boost::asio::serial_port port_;
};

/**
 * Set options on serial port.
 * @param opt Option to set
 * @param name Name for debug
 * @return
 */
template<typename SettableSerialPortOption>
bool UARTConnection::set_settings(const SettableSerialPortOption& opt,std::string name) {
	try{
	port_.set_option(opt);
	}catch(boost::system::system_error& se){
		WARNING("UART: "<< se.what()<<". Invalid \""<< name <<"\"");
	}
	return true;
}

} /* namespace freejtag */
#endif /* UARTCONNECTION_H_ */
