/*
 * ConnectionBundle.cpp
 *
 *  Created on: Jan 6, 2013
 *      Author: bachelor
 */

#include "ConnectionBundle.h"
#include <debug.h>

#include <boost/bind.hpp>

namespace freejtag {



void ConnectionBundle::addConnection(Connection::pointer conn) {
	connections_.insert(conn);
}



void ConnectionBundle::removeConnection(Connection::pointer conn) {
    conn->close();
	connections_.erase(conn);
}

void ConnectionBundle::close_all_connections() {
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::close,_1));
}

} /* namespace freejtag */


