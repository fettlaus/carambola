/*
 * MessageType.h
 *
 *  Created on: Dec 29, 2012
 *      Author: fettlaus
 */

#ifndef MESSAGETYPE_H_
#define MESSAGETYPE_H_

#include <stdint.h>

namespace freejtag {
enum MessageTypeEnum {MESS,UART,SPID,STIM,PING,PONG,GSET,SSET,SETT,ERROR};
class MessageType {
private:
	uint8_t value_;
	MessageTypeEnum enum_;
	uint8_t TypeToInt(MessageTypeEnum);
	MessageTypeEnum IntToType(uint8_t);
public:
	MessageType(MessageTypeEnum type);
	MessageType(uint8_t type);
	uint8_t getInt();
	MessageTypeEnum getType();
};

} /* namespace freejtag */
#endif /* MESSAGETYPE_H_ */
