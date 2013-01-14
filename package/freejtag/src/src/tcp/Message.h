/**
 * @file Message.h
 * @date Dec 27, 2012
 * @author Arne Wischer
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <boost/asio/buffer.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <stdint.h>

namespace asio = boost::asio;

namespace freejtag
{

/**
 * This enum is used to specify the type of the Message.
 */
enum MessageType {
    MESS, ///< 0x01: Common message to target.  Max size is body_max_length
    UART, ///< 0x02: Message received on the UART port of server.
    SPID, ///< 0x03: @todo what is this
    STIM, ///< 0x04: Set time
    PING, ///< 0x05: Ping!
    PONG, ///< 0x06: Answer to Ping!
    GSET, ///< 0x07: request settings
    SSET, ///< 0x08: send settings
    SETT, ///< 0x09: @todo what is this
    ERROR ///< 0x00: Error. Message invalid
};

/**
 * This is a single Message, which can be received from and sent to a Connection.
 * If it is created with the default constructor, it will appear as a ERROR message,
 * which can act as a placeholder. After reading data into the message it's
 * decode_header() function should be called to generate the necessary fields. Access to a Message
 * is only possible through its Message::pointer.
 *
 * <a href="http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_message.hpp">Useful example of
 *  designing a message</a>
 */
class Message: public boost::enable_shared_from_this<Message>
{

public:
    typedef boost::shared_ptr<Message> pointer; ///< We use smart pointers to access instances of this class.

    bool decode_header();
    ~Message();
    std::vector<asio::const_buffer> toBuffers() const; ///< Buffer useful for sending via Connection
    size_t getLength() const;
    uint32_t getTimestamp() const;
    void setTimestamp(uint32_t time);
    MessageType getType() const;
    void setType(MessageType type);
    static pointer createMessage(MessageType type = ERROR, std::string = "", uint32_t timestamp = 0); ///< Create a new Message and get its Message::pointer
private:
    friend std::ostream& operator<<(std::ostream& o, const Message& msg);
    static uint8_t TypeToInt(MessageType);
    static MessageType IntToType(uint8_t unsignedChar);
    Message(MessageType type, std::string, uint32_t timestamp);

    /**
     * The (fixed) length of the header in byte.
     */
    enum {
        header_length = 7
    };

    /**
     * Maximum allowed length of the body in byte.
     */
    enum {
        body_max_length = 512
    };

    uint8_t type_; ///< Type of this Message
    uint16_t length_; ///< Length of this Message
    uint32_t timestamp_; ///< Timestamp of this Message
    char data_[header_length + body_max_length]; ///< Data of this message (header + body)
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
