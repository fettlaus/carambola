/*
 * Message.h
 *
 *  Created on: Dec 27, 2012
 *      Author: fettlaus
 */

#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <boost/asio/buffer.hpp>

#ifndef MESSAGE_H_
#define MESSAGE_H_
namespace asio = boost::asio;

namespace freejtag {

enum MessageType {MESS,UART,SPID,STIM,PING,PONG,GSET,SSET,SETT,ERROR};

class Message{

public:
	enum{header_length=7};
	enum{body_max_length=512};
	char* body();
	char* header();
	bool decode_header();
	bool encode_header();
	Message(MessageType type,uint32_t timestamp);
	Message();
	~Message();
	std::size_t BodyLength() const;
	void BodyLength(std::size_t bodyLength);
	const char* Data() const;
	const char* getData() const;
	size_t size();
	std::vector<asio::const_buffer> to_buffers();
	uint8_t TypeToInt(MessageType);
	MessageType IntToType(uint8_t);
private:
	//MessageType *type_;
	uint8_t type_;
	uint16_t length_;
	uint32_t timestamp_;
	char data_[header_length+body_max_length];
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
