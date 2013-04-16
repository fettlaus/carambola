/**
 * @file MessageTarget.h
 * @date Jan 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef MESSAGETARGET_H_
#define MESSAGETARGET_H_

#include <network/Message.h>

namespace freejtag {

class MessageTarget {
public:
    virtual ~MessageTarget()=0;
    void deliver(const Message::pointer);
protected:
    MessageTarget();
};

} /* namespace freejtag */
#endif /* MESSAGETARGET_H_ */
