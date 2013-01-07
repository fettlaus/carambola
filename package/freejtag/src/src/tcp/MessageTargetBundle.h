/*
 * MessageTargetBundle.h
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#ifndef MESSAGETARGETBUNDLE_H_
#define MESSAGETARGETBUNDLE_H_

#include "ConnectionBundle.h"

namespace freejtag {

class MessageTargetBundle: public freejtag::ConnectionBundle {

public:
	void addConnection(Connection::pointer conn);
	bool sendBroadcast(const Message& msg);
	bool sendMessage(MessageTarget& target,const Message& msg);
};

} /* namespace freejtag */
#endif /* MESSAGETARGETBUNDLE_H_ */
