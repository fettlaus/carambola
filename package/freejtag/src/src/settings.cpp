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

settings::settings(int argc, char* argv[]):desc(po::options_description("Options")) {
	using namespace po;


	uart::parity par;
	map = new variables_map;
	options_description uart_options("UART Settings");
	uart_options.add_options()
			("device",value<std::string>()->default_value("/dev/ttyS0"),"Device to open")
			("baud",value<unsigned int>()->default_value(9600),"Baudrate to use with port")
			("parity",value<uart::parity>()->default_value(uart::parity(),"none"),"Parity")
			("flow_control",value<uart::flow_control>()->default_value(uart::flow_control(),"none"),"Flow control")
			("stop_bits",value<uart::stop_bits>()->default_value(uart::stop_bits(),"one"),"Stop bits")
			("data",value<unsigned int>()->default_value(8),"Size of character");
	options_description tcp_options("Network Settings");
	tcp_options.add_options()
			("port",value<uint16_t>()->default_value(12323),"Port");
	options_description desc2("Common settings");
	desc2.add_options()
			("help,?", "Print this help message")
			("debug", value<bool>(), "Enable Debug")
			("detached",value<bool>()->zero_tokens()->default_value(false),"Enable detaching")
			("threads",value<unsigned char>()->default_value(1),"Number of Threads [unused]")
	        ("ping",value<unsigned int>()->default_value(0),"Send Message \"PING!\" every x microsecs");
	options_description cmd("Settings");
	cmd.add(desc2).add(tcp_options).add(uart_options);
	store(parse_command_line(argc,argv,cmd),map);
	//TODO: Catch parse errors
	// TODO: parse config file
	//store(parse_config_file<char>(get_filename(), desc), map);
	notify(map);
	// handle input
	if(map.count("help")){
		std::cout << cmd << std::endl;
		// Abort program!
		exit(0);
	}

}
settings::~settings() {
	//TODO: Save settings
}
void settings::save_file() {

}
const char* settings::get_filename() {
#ifdef DEBUG
	return "conf/freejtag.cfg";
#else
	std::stringstream s;
	//s << 'SYSCONFDIR' << "/" << PACKAGE << ".cfg" << std::endl;
	//return s.str().c_str();
	return "file";
#endif
}



}
