/**
 * @file ConnectionBundle.cpp
 * @date Jan 7, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "ConnectionBundle.h"

namespace freejtag {

/**
 * Send a broadcast. This method calls the deliver() function for every Connection in this bundle.
 * @param msg Message to deliver
 * @return Always true (unused)
 * @todo Catch errors and return error state
 */
bool ConnectionBundle::send_broadcast(const Message::pointer msg) {
    PRINT("Sending Broadcast");
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::deliver,_1,boost::ref(msg)));
    return true;
}

/**
 * Add a new Connection to the bundle. A broadcast will be sent to all Connection instances before
 * adding the new Connection.
 * @param conn The new Connection
 */
void ConnectionBundle::add_connection(Connection::pointer conn) {
    this->send_broadcast(Message::create_message(Message::MESS,"New Connection!"));
    connections_.insert(conn);
}

/**
 * Remove a single Connection from the bundle. The close() method of the Connection will be called
 * before removing the Connection.
 * @param conn The Connection to be removed
 * @todo Return state of removal (true/false)
 */
void ConnectionBundle::remove_connection(Connection::pointer conn) {
    conn->close();
    connections_.erase(conn);
}

/**
 * Close all Connection instances. This simply calls close() for every Connection in this bundle.
 */
void ConnectionBundle::close_all_connections() {
    std::for_each(connections_.begin(),connections_.end(),boost::bind(&Connection::close,_1));
}

} /* namespace freejtag */
