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

bool MessageTargetBundle::send_broadcast(const Message::pointer msg) {
    PRINT("Sending Broadcast");
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::deliver,_1,boost::ref(msg)));
    return true;
}

void MessageTargetBundle::add_connection(Connection::pointer conn) {
    this->send_broadcast(Message::create_message(Message::MESS,"New Connection!"));
    ConnectionBundle::add_connection(conn);
}

} /* namespace freejtag */
