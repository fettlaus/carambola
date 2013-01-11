/*
 * NetworkServiceTypedef.h
 *
 *  Created on: Jan 10, 2013
 *      Author: bachelor
 */

#ifndef NETWORKSERVICETYPEDEF_H_
#define NETWORKSERVICETYPEDEF_H_

#include "../util/BlockingQueue.h"
//#include "Connection.h"
//#include "Message.h"

namespace freejtag{
class Connection;
class Message;
typedef std::pair< boost::shared_ptr< Connection >,boost::shared_ptr< Message > > MessageDatagram;
typedef BlockingQueue< MessageDatagram > MessageDatagramQueue;
typedef BlockingQueue< Message::pointer > MessageQueue;
}

#endif /* NETWORKSERVICETYPEDEF_H_ */
