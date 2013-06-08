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

/**
 * Used to propagate connection errors.
 * If a ConnectionException occurs, a ConnectionInfo should be appended to trace the problem back to
 * the Connection on which it happened. This can be done by using the streaming operator &lt;&lt;
 * @see ConnectionException
 */
typedef boost::error_info< struct tag_connection_info,boost::shared_ptr< Connection > > ConnectionInfo;

/**
 * Used to signal errors which happened on a Connection.
 * A ConnectionInfo should be appended to this Exception to trace back the source of the error.
 * <br/><a href="http://www.boost.org/doc/libs/1_49_0/libs/exception/doc/tutorial_transporting_data.html">
 * How to propagate information with exceptions</a>
 * @see ConnectionInfo
 */
struct ConnectionException: virtual boost::exception, virtual std::exception { };
}

#endif /* CONNECTIONEXCEPTION_H_ */
