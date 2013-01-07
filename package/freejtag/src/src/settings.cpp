/*
 * settings.c
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */

//#include "freejtag.h"
#include "settings.h"

#include <stdio.h>
#include <boost/program_options.hpp>
#include <boost/program_options/variables_map.hpp>

namespace freejtag {

po::variables_map &settings::get_map() {
	return map;
}
settings::settings(int argc, char* argv[]):desc(po::options_description("Options")) {
	using namespace po;
	map = new variables_map;
	desc.add_options()("debug", value<bool>(), "Enable Debug")
			("detached",value<bool>()->zero_tokens()->default_value(false),"Enable detaching");
	store(parse_command_line(argc,argv,desc),map);
	//store(parse_config_file<char>(get_filename(), desc), map);
	notify(map);
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
	//s << 'SYSCONFDIR' << "/" << PACKAGE << ".cfg" << std::endl;
	//return s.str().c_str();
	return "file";
#endif
}



}
