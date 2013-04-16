/**
 * @file ConnectionBundle.h
 * @date Jan 6, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef CONNECTIONBUNDLE_H_
#define CONNECTIONBUNDLE_H_

#include "Connection.h"

#include <set>

namespace freejtag {
typedef std::set<Connection::pointer> ConnectionList;
class ConnectionBundle{
public:
    void addConnection(Connection::pointer conn);
    void removeConnection(Connection::pointer conn);
    void close_all_connections();
protected:
    ConnectionList connections_;
};

} /* namespace freejtag */
#endif /* CONNECTIONBUNDLE_H_ */
