/*
 * freejtag.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef FREEJTAG_H_
#define FREEJTAG_H_

#include "settings.h"
#include "tcp/NetworkService.h"
#include "tcp/Message.h"
#include "uart/UARTService.h"
#include <boost/asio/io_service.hpp>
#include <utility>

namespace freejtag{
class Freejtag{
private:
	boost::asio::io_service* io_service_;
	settings prog_settings;
	NetworkService prog_network;
	UARTService uart_service_;

public:
	Freejtag(int argc, char* argv[]);
	~Freejtag();
	int run();
};
}

#endif /* FREEJTAG_H_ */
