/**
 * @file MessageTarget.cpp
 * @date Jan 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
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

