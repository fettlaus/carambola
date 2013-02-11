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

namespace freejtag {

/**
 * This enum is used to specify the type of the Message.
 */
enum MessageType {
    ERROR, ///< 0x00: Error. Message invalid
    MESS, ///< 0x01: Common message to target.  Max size is body_max_length (TCP)
    UART, ///< 0x02: Message received on the UART port of server. (TCP)
    SPID, ///< 0x03: place holder
    STIM, ///< 0x04: Set time (UDP)
    PING, ///< 0x05: Ping! (UDP)
    PONG, ///< 0x06: Answer to Ping! (UDP)
    GSET, ///< 0x07: place holder
    SSET, ///< 0x08: place holder
    SETT, ///< 0x09: place holder
    EXIT
};

/**
 * This is a single Message, which can be received from and sent to a Connection.
 * If it is created with the default constructor, it will appear as a ERROR message,
 * which can act as a placeholder. After reading data into the message it's
 * Message::decode_header() function should be called to generate the necessary fields. Access to a Message
 * is only possible through its Message::pointer.
 *
 * <a href="http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_message.hpp">Useful example of
 *  designing a message</a>
 */
class Message: public boost::enable_shared_from_this<Message> {

public:
    typedef boost::shared_ptr<Message> pointer; ///< We use smart pointers to access instances of this class.
    typedef uint64_t MessageTimestamp; ///< Size of the timestamp.
    typedef uint8_t MessageType_; ///< Size of the MessageType
    typedef uint16_t MessageLength_; ///< Size of the MessageLength

    int decode_header();
    ~Message();
    std::vector<asio::const_buffer> to_buffers() const; ///< Buffer useful for sending via Connection
    size_t get_length() const;
    MessageTimestamp get_timestamp() const;
    void set_timestamp(MessageTimestamp time);
    MessageType get_type() const;
    void set_type(MessageType type);
    static pointer create_message(MessageType type = ERROR, std::string = "", MessageTimestamp timestamp = 0); ///< Create a
    ///< new Message and get its Message::pointer
    char* get_header();
    char* get_body();

    /**
     * The (fixed) length of the header in byte.
     */
    enum {
        header_length = sizeof(MessageType_) + sizeof(MessageLength_) + sizeof(MessageTimestamp)
    };

    /**
     * Maximum allowed length of the body in byte.
     */
    enum {
        body_max_length = 512
    };

private:
    friend std::ostream& operator<<(std::ostream& o, const Message::pointer msg);
    static MessageType_ type_to_int(MessageType);
    static MessageType int_to_type(MessageType_ unsignedChar);
    Message(MessageType type, std::string, MessageTimestamp timestamp);
    MessageType_ type_; ///< Type of this Message
    MessageLength_ length_; ///< Length of this Message (big endian)
    MessageTimestamp timestamp_; ///< Timestamp of this Message (big endian)
    char data_[header_length + body_max_length]; ///< Data of this message (header + body)
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
