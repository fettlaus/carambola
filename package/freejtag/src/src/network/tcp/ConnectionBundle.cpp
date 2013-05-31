/**
 * @file ConnectionBundle.cpp
 * @date Jan 6, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "ConnectionBundle.h"
#include <debug.h>

#include <boost/bind.hpp>

namespace freejtag {

void ConnectionBundle::add_connection(Connection::pointer conn) {
    connections_.insert(conn);
}

void ConnectionBundle::remove_connection(Connection::pointer conn) {
    conn->close();
    connections_.erase(conn);
}

void ConnectionBundle::close_all_connections() {
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::close,_1));
}

} /* namespace freejtag */
