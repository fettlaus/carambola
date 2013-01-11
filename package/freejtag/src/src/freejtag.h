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
#include <utility>

//class freejtag::telnet;
namespace freejtag{
class freejtag{
private:
	settings prog_settings;
	NetworkService prog_network;
	UARTService uart_service_;
public:
	freejtag(int argc, char* argv[]);
	~freejtag();
	int run();
};
}

#endif /* FREEJTAG_H_ */
