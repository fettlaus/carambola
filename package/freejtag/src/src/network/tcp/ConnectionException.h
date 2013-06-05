/**
 * @file ConnectionException.h
 * @date Jan 10, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef CONNECTIONEXCEPTION_H_
#define CONNECTIONEXCEPTION_H_

#include <boost/exception/all.hpp>
#include <iostream>

namespace freejtag{
class Connection;
typedef boost::error_info< struct tag_connection_info,boost::shared_ptr< Connection > > connection_info;

/**
 * http://www.boost.org/doc/libs/1_49_0/libs/exception/doc/tutorial_transporting_data.html
 */
struct connection_exception: virtual boost::exception, virtual std::exception { };
}

#endif /* CONNECTIONEXCEPTION_H_ */
