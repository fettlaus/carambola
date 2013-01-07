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

enum MessageType {MESS, ///< 0x01: Common message to target.  Max size is body_max_length
	UART, ///< 0x02: Message received on the UART port of server.
	SPID, ///< 0x03: TODO
	STIM, ///< 0x04: Set time
	PING, ///< 0x05: Ping!
	PONG, ///< 0x06: Answer to Ping!
	GSET, ///< 0x07: request settings
	SSET, ///< 0x08: send settings
	SETT, ///< 0x09: TODO
	ERROR ///< 0x00: Error. Message invalid
};

/**
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_message.hpp
 */
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
	static uint8_t TypeToInt(MessageType);
	static MessageType IntToType(uint8_t);
	uint8_t type_;
	uint16_t length_;
	uint32_t timestamp_;
	char data_[header_length+body_max_length];
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
