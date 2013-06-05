/**
 * @file Message.h
 * @date Dec 27, 2012
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <boost/asio/buffer.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <stdint.h>
#include <common/TimeKeeper.h>
#include <debug.h>
#include <cstring>
#include <boost/detail/endian.hpp>

namespace asio = boost::asio;

namespace freejtag {

/**
 * This is a single Message, which can be received from and sent to a Connection.
 * If it is created with the default constructor, it will appear as a MessageType::ERROR message,
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

    /**
     * This enum is used to specify the type of the Message.
     */
    enum Type {
        ERROR, ///< 0x00: Error. Message invalid
        MESS, ///< 0x01: Common message to target.  Max size is body_max_length (TCP)
        UART, ///< 0x02: Message received on the UART port of server. (TCP)
        SPID, ///< 0x03: place holder
        STIM, ///< 0x04: Set time (UDP)
        PING, ///< 0x05: Ping! (UDP+TCP)
        PONG, ///< 0x06: Answer to Ping! (UDP+TCP)
        GSET, ///< 0x07: place holder
        SSET, ///< 0x08: place holder
        SETT, ///< 0x09: place holder
        EXIT ///< 0x10: shutdown server (TCP)
    };

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

    /**
     * Fixed length of a single UDP Message. UDP Messages have fixed length of
     * header and the timestamp in its body. The Timestamp will also be used as a sequence number.
     */
    enum {
        udp_packet_length = header_length + sizeof(MessageTimestamp)
    };

    int decode_header();
    ~Message();
    std::vector<asio::const_buffer> to_buffers() const;
    size_t get_length() const;
    MessageTimestamp get_timestamp() const;
    MessageTimestamp get_payload() const;
    void set_timestamp(MessageTimestamp time);
    Message::Type get_type() const;
    void set_type(Message::Type type);
    static pointer create_message(Message::Type type = ERROR, std::string = "", MessageTimestamp timestamp = 0);
    char* get_header();
    char* get_body();
private:
    friend std::ostream& operator<<(std::ostream& o, const Message::pointer msg);
    static MessageType_ type_to_int(Message::Type);
    static Message::Type int_to_type(MessageType_ unsignedChar);
    Message(Message::Type type, std::string, MessageTimestamp timestamp);
    MessageType_ type_; ///< Type of this Message
    MessageLength_ length_; ///< Length of this Message (big endian)
    MessageTimestamp timestamp_; ///< Timestamp of this Message (big endian)
    char data_[header_length + body_max_length]; ///< Data of this message (header + body)
};

} /* namespace freejtag */
#endif /* MESSAGE_H_ */
