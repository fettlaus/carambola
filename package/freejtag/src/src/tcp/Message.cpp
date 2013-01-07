/*
 * Message.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: fettlaus
 */

#include "Message.h"
#include "debug.h"

#include <cstring>

namespace freejtag {
Message::Message(MessageType type,std::string body,uint32_t timestamp):length_(body.length()),type_(TypeToInt(type)),timestamp_(timestamp) {
	memset(data_,0,header_length+body_max_length);
	const char* tmp = body.c_str();
	memcpy(data_+header_length,tmp,strlen(tmp));
	/**
	 * http://www.boost.org/doc/libs/1_52_0/doc/html/date_time/posix_time.html
	 * http://stackoverflow.com/questions/6734375/c-boost-get-current-time-in-milliseconds
	 */
	//Need to generate own timestamp
	if(timestamp_ == 0){
		using namespace boost::posix_time;
		using namespace boost::gregorian;
		ptime zero(date(day_clock::local_day()));
		ptime now(microsec_clock::local_time());
		time_duration diff = now - zero;
		timestamp_ = diff.total_milliseconds();
	}

	PRINT("Message(" << (int)type_ << "," << (int)length_ << "," << (long)timestamp_ << ")=\"" << body << "\"");
}

Message::~Message(){
	;
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
	type_ = atoi(buffer);

	buffer[0] = '\0';
	std::strncat(buffer,data_+sizeof(type),sizeof(length_));
	length_ = atoi(buffer);

	buffer[0] = '\0';
	std::strncat(buffer,data_+sizeof(type)+sizeof(length_),sizeof(timestamp_));
	timestamp_ = atoi(buffer);

	return true;
}

bool Message::encode_header() {
	PRINT(strnlen(data_+header_length,body_max_length));
	length_ = strnlen(data_+header_length,body_max_length);
	return true;
}
/*
char* Message::body() {
	return data_+header_length;
}

const char* Message::getData() const {
	return data_;
}
*/

//Message::Message():type_(ERROR),length_(0),timestamp_(0){
//
//}



size_t Message::getLength() const {
	return length_;
}

std::vector<asio::const_buffer> Message::toBuffers() const {
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(asio::buffer(&type_,1));
	buffers.push_back(asio::buffer(&length_,2));
	buffers.push_back(asio::buffer(&timestamp_,4));
	if(type_ == 0x01){
		buffers.push_back(asio::buffer(data_+header_length,length_));
	}
	return buffers;
}

uint8_t Message::TypeToInt(MessageType messageTypeEnum) {
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

uint32_t Message::getTimestamp() const {
	return timestamp_;
}

void Message::setTimestamp(uint32_t time) {
	timestamp_ = time;
}

MessageType Message::getType() const {
	return IntToType(type_);
}

void Message::setType(MessageType type) {
	type_ = TypeToInt(type);
}

MessageType Message::IntToType(uint8_t unsignedChar) {
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
} /* namespace freejtag */
