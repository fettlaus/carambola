/*
 * MessageTarget.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#include "MessageTarget.h"
#include "debug.h"

namespace freejtag {


bool MessageTarget::isBroadcast() {
	return broadcast_;
}

MessageTarget::MessageTarget(bool broadcast):broadcast_(broadcast){

}

void MessageTarget::deliver(const Message&) {
	PRINT("False print to broadcast!");
}

} /* namespace freejtag */

