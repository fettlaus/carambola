/*
 * settings.h
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <boost/program_options.hpp>
#include <boost/asio/serial_port_base.hpp>
#include <string>

namespace po = boost::program_options;

namespace freejtag {

class settings{
private:
	po::variables_map map;
	const char* get_filename();
	void set_descs();
public:
	settings(int argc, char* argv[]);
	~settings();
	po::variables_map &get_map();
	template <typename P> const P get_value(const char* val) const;
	void save_file();
};
}
#include "settings.hpp"

#endif /* SETTINGS_H_ */
