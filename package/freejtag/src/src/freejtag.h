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
#include "tcp/BlockingQueue.h"
#include "tcp/Message.h"
#include <utility>

//class freejtag::telnet;
namespace freejtag{
class freejtag{
private:
	MessageQueue message_output_buffer_;
	MessageQueue message_input_buffer_;
	settings prog_settings;
	NetworkService prog_network;
public:
	freejtag(int argc, char* argv[]);
	~freejtag();
	int run();
};
}

#endif /* FREEJTAG_H_ */
