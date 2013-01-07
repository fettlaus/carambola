/*
 * MessageTarget.h
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#ifndef MESSAGETARGET_H_
#define MESSAGETARGET_H_
#include "Message.h"

namespace freejtag {

class MessageTarget {
public:
	bool isBroadcast();
	void deliver(const Message&);
private:
	MessageTarget(bool broadcast = true);
	bool broadcast_;
};

} /* namespace freejtag */
#endif /* MESSAGETARGET_H_ */
