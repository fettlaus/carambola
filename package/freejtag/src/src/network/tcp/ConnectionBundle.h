/**
 * @file ConnectionBundle.h
 * @date Jan 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef MESSAGETARGETBUNDLE_H_
#define MESSAGETARGETBUNDLE_H_

#include "Connection.h"

#include <set>

namespace freejtag {

/**
 *
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
#endif /* MESSAGETARGETBUNDLE_H_ */
