/*
 * settings.c
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */

//#include "freejtag.h"
#include "settings.h"
#include "uart/UARTTypes.h"

#include <stdio.h>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>


namespace freejtag {

po::variables_map &settings::get_map() {
	return map;
}

settings::settings(int argc, char* argv[]) {
	using namespace po;

	uart::parity par;
	options_description uart_options("UART Settings");
	uart_options.add_options()
			("uart.device",value<std::string>()->default_value("/dev/ttyS0"),"Device to open")
			("uart.baud",value<unsigned int>()->default_value(9600),"Baudrate to use with port")
			("uart.parity",value<uart::parity>()->default_value(uart::parity(),"none"),"Parity")
			("uart.flow_control",value<uart::flow_control>()->default_value(uart::flow_control(),"none"),"Flow control")
			("uart.stop_bits",value<uart::stop_bits>()->default_value(uart::stop_bits(),"one"),"Stop bits")
			("uart.data",value<unsigned int>()->default_value(8),"Size of character");
	options_description tcp_options("Network Settings");
	tcp_options.add_options()
            ("network.port",value<unsigned int>()->default_value(12323),"UDP Port");
	options_description desc2("Common settings");
	desc2.add_options()
			("help,?", "Print this help message")
			("common.debug", value<bool>(), "Enable Debug")
			("common.detached",value<bool>()->zero_tokens()->default_value(false),"Enable detaching")
			("common.threads",value<unsigned char>()->default_value(1),"Number of Threads [unused]")
	        ("common.ping",value<unsigned int>()->default_value(0),"Send Message \"PING!\" every x microsecs");
	desc2.add(tcp_options).add(uart_options);
	store(parse_command_line(argc,argv,desc2),map);
	//TODO: Catch parse errors
	store(parse_config_file<char>(get_filename(), desc2), map);
	notify(map);
	// handle input
	if(map.count("help")){
		std::cout << desc2 << std::endl;
		// Abort program!
		exit(0);
	}

}

settings::~settings() {
}

void settings::save_file() {

}
const char* settings::get_filename() {
#ifdef DEBUG
	return "conf/freejtag.cfg";
#else
	std::stringstream s;
	s << SYSCONFDIR << "/freejtag.cfg" << std::endl;
	return s.str().c_str();
	return "file";
#endif
}



}
