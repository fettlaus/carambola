/*
 * ConnectionBundle.h
 *
 *  Created on: Jan 6, 2013
 *      Author: bachelor
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
