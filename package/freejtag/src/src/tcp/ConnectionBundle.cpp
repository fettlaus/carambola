/*
 * ConnectionBundle.cpp
 *
 *  Created on: Jan 6, 2013
 *      Author: bachelor
 */

#include "ConnectionBundle.h"
#include "debug.h"

#include <boost/bind.hpp>

namespace freejtag {

bool freejtag::ConnectionBundle::sendBroadcast(const Message& msg) {
	PRINT("Sending Broadcast");
	std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::deliver,_1,boost::ref(msg)));
	return true;
}

void freejtag::ConnectionBundle::addConnection(Connection::pointer conn) {
	this->sendBroadcast(Message(MESS,"New Connection!"));
	connections_.insert(conn);
}

void freejtag::ConnectionBundle::removeConnection(Connection::pointer conn) {
	connections_.erase(conn);
}

} /* namespace freejtag */


