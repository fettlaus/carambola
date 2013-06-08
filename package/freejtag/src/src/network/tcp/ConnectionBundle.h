/**
 * @file ConnectionBundle.h
 * @date Jan 7, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef CONNECTIONBUNDLE_H_
#define CONNECTIONBUNDLE_H_

#include "Connection.h"

#include <algorithm>
#include <set>

namespace freejtag {

/**
 * Used to store a number of Connections.
 * This class stores a number of unique Connections and offers some functionality to communicate with
 * all Connection instances at once.
 */
class MessageTargetBundle {
public:
    void add_connection(Connection::pointer conn);
    void remove_connection(Connection::pointer conn);
    void close_all_connections();
    bool send_broadcast(const Message::pointer msg);
protected:
    typedef std::set<Connection::pointer> ConnectionList; ///< Type of internal storage (set)
    ConnectionList connections_; ///< Storage for all Connection instances
};

} /* namespace freejtag */
#endif /* CONNECTIONBUNDLE_H_ */
