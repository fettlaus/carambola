/**
 * @file settings.cpp
 * @date Dec 25, 2012
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "settings.h"
#include "uart/UARTTypes.h"

#include <debug.h>

#include <stdio.h>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include <fstream>

namespace freejtag {

po::variables_map &settings::get_map() {
	return map;
}

settings::settings(int argc, char* argv[]) {
    using namespace po;

    uart::parity par;
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
            ("port",value<unsigned int>()->default_value(12323),"UDP Port");
    options_description desc2("Common settings");
    desc2.add_options()
            ("help,?", "Print this help message")
            ("ping",value<unsigned int>()->default_value(0),"Send Message \"PING!\" every x microsecs");
    desc2.add(tcp_options).add(uart_options);
    store(parse_command_line(argc,argv,desc2),map);

    try{
        store(parse_config_file<char>(get_filename().c_str(), desc2), map);
    }catch(std::ifstream::failure& e){
        WARNING("Error: " << e.what() << " while reading "<<get_filename());
    }
    notify(map);
    // handle input
    if(map.count("help")){
        std::cout << "FreeJTAG Version 0.2.0" << std::endl;
        std::cout << desc2 << std::endl;
        // Abort program!
        exit(0);
    }

}

settings::~settings() { }

void settings::save_file() { }

/**
 * Switch to internal config-file if running in DEBUG
 * @return
 */
const std::string settings::get_filename() {
#ifdef DEBUG
    return "conf/freejtag.cfg";
#else
    std::stringstream s;
    s << SYSCONFDIR << "/freejtag.cfg";
    return s.str();
#endif
}

}
