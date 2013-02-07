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
	connections_.erase(conn);
}

} /* namespace freejtag */


