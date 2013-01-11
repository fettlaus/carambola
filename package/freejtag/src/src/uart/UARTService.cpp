/*
 * UARTService.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#include "UARTService.h"
#include "UARTTypes.h"

namespace freejtag {

UARTService::UARTService(settings& settings):uart_thread_(boost::bind(&UARTService::read_line,this)),
		shutdown_(false),
		uart_connection_(new UARTConnection(*io_service_)),
		io_service_(new boost::asio::io_service),
		settings_(settings){
	reload_settings();
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
	uart_connection_->close();
	uart_connection_->open(settings_.get_value<std::string>("device"));
	uart_connection_->set_settings<uart::parity>(settings_.get_value<uart::parity>("parity"));
	uart_connection_->set_settings<uart::flow_control>(settings_.get_value<uart::flow_control>("flow_control"));
	uart_connection_->set_settings<uart::stop_bits>(settings_.get_value<uart::stop_bits>("stop_bits"));
	uart_connection_->set_settings<serial_port_base::baud_rate>(serial_port::baud_rate(settings_.get_value<unsigned int>("baud")));
	uart_connection_->set_settings<serial_port_base::character_size>(serial_port::character_size(settings_.get_value<unsigned int>("data")));
}

void UARTService::read_line() {
	while(!shutdown_){
		//uart_buffer_.push(std::string("Test!"));
		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
	}
}

} /* namespace freejtag */
