/**
 * @file MessageTarget.h
 * @date Jan 7, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef MESSAGETARGET_H_
#define MESSAGETARGET_H_

#include <network/Message.h>

namespace freejtag {

/**
 * Interface for a target which can receive a Message. This target only needs to respond to a deliver()
 * method.
 */
class MessageTarget {
public:
    virtual ~MessageTarget() {};

    /**
     * Deliver a single Message. This function delivers a single Message to the implementing
     * target.
     * @param mess Message to deliver
     */
    virtual void deliver(const Message::pointer mess) = 0;
};

} /* namespace freejtag */
#endif /* MESSAGETARGET_H_ */
