/**
 * @file MessageTargetBundle.cpp
 * @date Jan 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "MessageTargetBundle.h"
#include <debug.h>
#include <boost/bind.hpp>
#include <algorithm>

namespace freejtag {

bool MessageTargetBundle::sendBroadcast(const Message::pointer msg) {
    PRINT("Sending Broadcast");
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::deliver,_1,boost::ref(msg)));
    return true;
}

void MessageTargetBundle::addConnection(Connection::pointer conn) {
    this->sendBroadcast(Message::create_message(MESS,"New Connection!"));
    ConnectionBundle::addConnection(conn);
}

} /* namespace freejtag */
