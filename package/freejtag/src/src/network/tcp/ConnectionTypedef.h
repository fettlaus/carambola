/**
 * @file ConnectionTypedef.h
 * @date Jan 10, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef CONNECTIONTYPEDEF_H_
#define CONNECTIONTYPEDEF_H_

#include <common/BlockingQueue.h>

namespace freejtag{
class Connection;
class Message;

/**
 * A single Datagram.
 * This Datagram consists of the shared_ptr to the Connection on which the Message arrived as well as the
 * shared_ptr to the Message itself.
 * @see Connection Message
 */
typedef std::pair< boost::shared_ptr< Connection >,boost::shared_ptr< Message > > MessageDatagram;

/**
 * The Buffer used for storing multiple MessageDatagram instances.
 * It facilitates a BlockingQueue for storage.
 * @see MessageDatagram BlockingQueue
 */
typedef BlockingQueue< MessageDatagram > NetworkBuffer;
}

#endif /* CONNECTIONTYPEDEF_H_ */
