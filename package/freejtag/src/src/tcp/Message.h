/*
 * Message.h
 *
 *  Created on: Dec 27, 2012
 *      Author: fettlaus
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <boost/asio/buffer.hpp>
//#include <cstdlib>
#include <stdint.h>
//#include <vector>

namespace asio = boost::asio;

namespace freejtag {

enum MessageType {MESS,UART,SPID,STIM,PING,PONG,GSET,SSET,SETT,ERROR};

class Message{

public:
	//char* body();
	//char* header();
	bool decode_header();
	bool encode_header();
	// ping: type
	// simple msg: type, body
	// extended msg: type, body, timestamp
	Message(MessageType type=ERROR, std::string = "", uint32_t timestamp = 0);
	//Message(MessageType type, char* body);
	//Message(MessageType type);
	//Message();
	~Message();
	//std::size_t BodyLength() const;
	//void BodyLength(std::size_t bodyLength);
	//const char* Data() const;
	//const char* getData() const;
	//size_t size();


	std::vector<asio::const_buffer> toBuffers() const;

	size_t getLength() const;
	uint32_t getTimestamp() const;
	void setTimestamp(uint32_t time);
	MessageType getType() const;
	void setType(MessageType type);
private:
	enum{header_length=7};
	enum{body_max_length=512};
	//MessageType *type_;
	uint8_t TypeToInt(MessageType);
	MessageType IntToType(uint8_t);
	uint8_t type_;
	uint16_t length_;
	uint32_t timestamp_;
	char data_[header_length+body_max_length];
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
