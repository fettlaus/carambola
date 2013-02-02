/*
 * UARTService.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#include "UARTService.h"
//#include "UARTTypes.h"

namespace freejtag {

UARTService::UARTService(boost::asio::io_service& io_service, UARTBuffer& buffer, settings& settings):uart_thread_(boost::bind(&UARTService::read_line,this)),
		shutdown_(false),
		uart_connection_(io_service_,buffer),
		io_service_(io_service),
		settings_(settings),
		uart_buffer_(buffer){
	//reload_settings();
	// get settings
	// start uart
	// start uartservice

}

UARTService::~UARTService() {
	// TODO Auto-generated destructor stub
}

std::string UARTService::get_line() {
	return "";
}

void UARTService::reload_settings() {
	using namespace boost::asio;
	uart_connection_.close();
	uart_connection_.open(device_);
}

void UARTService::open(std::string device) {
	uart_connection_.open(device);
}

///@todo: remove this thread, we are now async.
void UARTService::read_line() {
	while(!shutdown_){
		//uart_buffer_.push(std::string("Test!"));
		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
	}
}



} /* namespace freejtag */
