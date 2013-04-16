/**
 * @file MessageTargetBundle.h
 * @date Jan 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef MESSAGETARGETBUNDLE_H_
#define MESSAGETARGETBUNDLE_H_

#include "ConnectionBundle.h"

namespace freejtag {

class MessageTargetBundle: public freejtag::ConnectionBundle {

public:
    void addConnection(Connection::pointer conn);
    bool sendBroadcast(const Message::pointer msg);
};

} /* namespace freejtag */
#endif /* MESSAGETARGETBUNDLE_H_ */
