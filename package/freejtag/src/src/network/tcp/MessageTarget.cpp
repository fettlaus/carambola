/*
 * MessageTarget.cpp
 *
 *  Created on: Jan 7, 2013
 *      Author: bachelor
 */

#include "MessageTarget.h"
#include <debug.h>

namespace freejtag{

MessageTarget::MessageTarget(){

}

MessageTarget::~MessageTarget(){

}

void MessageTarget::deliver(const Message::pointer) {
	PRINT("False print to broadcast!");
}

} /* namespace freejtag */

