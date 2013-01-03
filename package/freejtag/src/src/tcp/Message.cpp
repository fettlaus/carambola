/*
 * Message.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: fettlaus
 */

#include "Message.h"
#include <cstring>

namespace freejtag {
Message::Message(MessageTypeEnum type,long timestamp):length_(0),type_(new MessageType(type)),timestamp_(timestamp) {
}

Message::~Message(){
	delete type_;
}

size_t Message::BodyLength() const {
	return length_;
}
/*
void Message::BodyLength(size_t bodyLength) {
	if(bodyLength>body_max_length){
		body_length_ = body_max_length;
	}else{
		body_length_ = bodyLength;
	}
}
*/

bool Message::decode_header() {
	char buffer[header_length+2] = "";
	uint8_t type;
	std::strncat(buffer,data_,sizeof(type));
	type = atoi(buffer);
	type_ = new MessageType(type);

	buffer[0] = '\0';
	std::strncat(buffer,data_+sizeof(type),sizeof(length_));
	length_ = atoi(buffer);

	buffer[0] = '\0';
	std::strncat(buffer,data_+sizeof(type)+sizeof(length_),sizeof(timestamp_));
	timestamp_ = atoi(buffer);

	return true;
}

bool Message::encode_header() {
	return true;
}

const char* Message::getData() const {
	return data_+header_length;
}
Message::Message():type_(new MessageType(ERROR)),length_(0),timestamp_(0){

}

} /* namespace freejtag */
