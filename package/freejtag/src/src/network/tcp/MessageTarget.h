/*
 * MessageTarget.h
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
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
