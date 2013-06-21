/**
 * @file UARTConnectionTypedef.h
 * @date Jan 13, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef UARTCONNECTIONTYPEDEF_H_
#define UARTCONNECTIONTYPEDEF_H_

#include <stdint.h>
#include <common/BlockingQueue.h>

namespace freejtag{

typedef std::pair< uint64_t, std::string > UARTMessage; ///< Single UART message with timestamp and message
typedef BlockingQueue< UARTMessage > UARTBuffer; ///< Storage for multiple UARTMessage instances

}

#endif /* UARTCONNECTIONTYPEDEF_H_ */
