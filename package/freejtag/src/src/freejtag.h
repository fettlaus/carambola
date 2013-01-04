/*
 * freejtag.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "settings.h"
#include "tcp/telnet.h"

#ifndef FREEJTAG_H_
#define FREEJTAG_H_
#ifdef DEBUG
#define PRINT(...) std::cout << __VA_ARGS__ << std::endl
#define WARNING(...) printf(__VA_ARGS__)
#define CRITICAL(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#define WARNING(...)
#define CRITICAL(...)
#endif
#define ERROR(...) g_error(__VA_ARGS__)

//class freejtag::telnet;
namespace freejtag{
class freejtag{
private:
	settings *prog_settings;
	telnet *prog_telnet;

public:
	freejtag(int argc, char* argv[]);
	~freejtag();
	int run();
};
}

#endif /* FREEJTAG_H_ */
