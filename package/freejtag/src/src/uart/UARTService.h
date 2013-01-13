/*
 * UARTService.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

#include "UARTConnection.h"
#include "UARTServiceTypedef.h"
//#include "../util/BlockingQueue.h"
//#include "../settings.h"
#include <boost/thread.hpp>

namespace freejtag {

//TODO: remove settings from UART
class settings;

class UARTService {
public:
	UARTService(boost::asio::io_service& io_service, UARTBuffer& buffer, settings& settings);
	virtual ~UARTService();
	std::string get_line();
	void open(std::string device);
	template<typename SettableSerialPortOption>
	void set_setting(const SettableSerialPortOption& option, std::string name);

private:
	void reload_settings();
	settings& settings_;
	boost::asio::io_service& io_service_;
	bool shutdown_;
	void read_line();
	UARTBuffer& uart_buffer_;
	boost::thread uart_thread_;
	UARTConnection uart_connection_;
	std::string device_;
};

/**
 * Set options on serial port.
 * @param opt Option to set
 * @param name Name for debug
 * @return
 */
template<typename SettableSerialPortOption>
void UARTService::set_setting(const SettableSerialPortOption& opt, std::string name) {
	try{
		uart_connection_.get_port().set_option(opt);
	}catch(boost::system::system_error& se){
		WARNING("UART: "<< se.what()<<". Invalid \""<< name <<"\"");
	}
}

} /* namespace freejtag */




#endif /* UARTSERVICE_H_ */
