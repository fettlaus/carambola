/*
 * ConnectionException.h
 *
 *  Created on: Jan 10, 2013
 *      Author: bachelor
 */

#ifndef CONNECTIONEXCEPTION_H_
#define CONNECTIONEXCEPTION_H_

#include <boost/exception/all.hpp>
#include <iostream>


namespace freejtag{
typedef boost::error_info<struct tag_connection_info,Connection::pointer> connection_info;

/**
 * http://www.boost.org/doc/libs/1_49_0/libs/exception/doc/tutorial_transporting_data.html
 */
struct connection_exception: virtual boost::exception, virtual std::exception { }; //(2)
}

#endif /* CONNECTIONEXCEPTION_H_ */
