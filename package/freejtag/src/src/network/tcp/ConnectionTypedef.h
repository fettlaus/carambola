/**
 * @file ConnectionTypedef.h
 * @date Jan 10, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef NETWORKSERVICETYPEDEF_H_
#define NETWORKSERVICETYPEDEF_H_

#include <common/BlockingQueue.h>

namespace freejtag{
class Connection;
class Message;
typedef std::pair< boost::shared_ptr< Connection >,boost::shared_ptr< Message > > MessageDatagram;
typedef BlockingQueue< MessageDatagram > NetworkBuffer;
}

#endif /* NETWORKSERVICETYPEDEF_H_ */
