/*
 * UARTService.cpp
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#include "UARTService.h"

namespace freejtag {

UARTService::UARTService():uart_thread_(boost::bind(&UARTService::read_line,this)) {
	// TODO Auto-generated constructor stub

}

UARTService::~UARTService() {
	// TODO Auto-generated destructor stub
}

std::string UARTService::get_line() {
	return "";
}

std::string UARTService::read_line() {
	return "";
}

} /* namespace freejtag */
