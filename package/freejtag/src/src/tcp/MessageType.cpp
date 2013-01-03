/*
 * MessageType.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: fettlaus
 */

#include "MessageType.h"

namespace freejtag {

MessageType::MessageType(MessageTypeEnum type) {
	value_ = TypeToInt(type);
	enum_ = type;
}

MessageType::MessageType(uint8_t type) {
	value_=type;
	enum_ = IntToType(type);
}

uint8_t MessageType::getInt() {
	return value_;
}

/**
 * MESS,UART,SPID,STIM,PING,PONG,GSET,SSET,SETT
 * @param messageTypeEnum
 * @return
 */
uint8_t MessageType::TypeToInt(MessageTypeEnum messageTypeEnum) {
	switch (messageTypeEnum) {
		case MESS:
			return 0x01;
		case UART:
			return 0x02;
		case SPID:
			return 0x03;
		case STIM:
			return 0x04;
		case PING:
			return 0x05;
		case PONG:
			return 0x06;
		case GSET:
			return 0x07;
		case SSET:
			return 0x08;
		case SETT:
			return 0x09;
		default:
			return 0;
	}
}
MessageTypeEnum MessageType::IntToType(uint8_t unsignedChar) {
	switch (unsignedChar) {
		case 0x01:
			return MESS;
		case 0x02:
			return UART;
		case 0x03:
			return SPID;
		case 0x04:
			return STIM;
		case 0x05:
			return PING;
		case 0x06:
			return PONG;
		case 0x07:
			return GSET;
		case 0x08:
			return SSET;
		case 0x09:
			return SETT;
		default:
			return ERROR;
	}
}

MessageTypeEnum MessageType::getType() {
	return enum_;
}

} /* namespace freejtag */
