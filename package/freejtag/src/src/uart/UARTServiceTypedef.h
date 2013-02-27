/*
 * UARTServiceTypedef.h
 *
 *  Created on: Jan 13, 2013
 *      Author: bachelor
 */

#ifndef UARTSERVICETYPEDEF_H_
#define UARTSERVICETYPEDEF_H_

#include <util/BlockingQueue.h>
namespace freejtag{
typedef std::pair< uint64_t, std::string > UARTMessage;
typedef BlockingQueue< UARTMessage > UARTBuffer;
}

#endif /* UARTSERVICETYPEDEF_H_ */