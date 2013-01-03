/*
 * Message.h
 *
 *  Created on: Dec 27, 2012
 *      Author: fettlaus
 */

#include "MessageType.h"
#include <cstdlib>
#include <stdint.h>

#ifndef MESSAGE_H_
#define MESSAGE_H_

namespace freejtag {

class Message{

public:
	enum{header_length=7};
	enum{body_max_length=512};
	char* body();
	char* header();
	bool decode_header();
	bool encode_header();
	Message(MessageTypeEnum type,long timestamp);
	Message();
	~Message();
	std::size_t BodyLength() const;
	void BodyLength(std::size_t bodyLength);
	const char* Data() const;
	const char* getData() const;

private:
	MessageType *type_;
	uint16_t length_;
	uint64_t timestamp_;
	char data_[header_length+body_max_length];
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
