/*
 * UARTService.h
 *
 *  Created on: Jan 11, 2013
 *      Author: bachelor
 */

#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

#include "../util/BlockingQueue.h"
#include <boost/thread.hpp>

namespace freejtag {

class UARTService {
public:
	UARTService();
	virtual ~UARTService();
	std::string get_line();
private:
	std::string read_line();
	boost::thread uart_thread_;
};

} /* namespace freejtag */
#endif /* UARTSERVICE_H_ */
