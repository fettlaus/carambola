/**
 * Message.cpp
 * @date Dec 27, 2012
 * @author Arne Wischer
 */

#include "Message.h"
#include "debug.h"
#include <cstring>

namespace freejtag
{

/**
 * Create a new message. This constructor is private, because new instances should be created by
 * Message::createMessage().
 * @param type The MessageType of the new Message
 * @param body The body-content of the new Message
 * @param timestamp The timestamp of the new Message
 */
Message::Message(MessageType type, std::string body, uint32_t timestamp) :
    length_(body.length()),
    type_(TypeToInt(type)),
    timestamp_(timestamp)
{
    // ensure data_ is zeroed
    memset(data_, 0, header_length + body_max_length);

    const char * tmp = body.c_str();

    // restrict length to maximum
    if (strlen(tmp) > body_max_length) {
        memcpy(data_ + header_length, tmp, body_max_length); ///< @todo fix terminating null
    } else {
        memcpy(data_ + header_length, tmp, strlen(tmp));
    }

    /**
     * <a href="http://www.boost.org/doc/libs/1_52_0/doc/html/date_time/posix_time.html">Posix-Time Documentation</a>
     * <a href="http://stackoverflow.com/questions/6734375/c-boost-get-current-time-in-milliseconds">How to calculate time in ms</a>
     */
    if (timestamp_ == 0) { // Need to generate own timestamp
        using namespace boost::posix_time;
        using namespace boost::gregorian;

        ptime zero(date(day_clock::local_day()));
        ptime now(microsec_clock::local_time());
        time_duration diff = now - zero;

        timestamp_ = diff.total_milliseconds();
    }

    PRINT(this << " created");
}

/**
 * Parse a Message to a std::ostream.
 * @param o Incoming ostroem
 * @param msg Message to parse
 * @return Outgoing ostream
 */
std::ostream & operator <<(std::ostream & o, const Message & msg)
{
    return o << "Message("
           << (int) msg.type_
           << ","
           << (int) msg.length_
           << ","
           << (int) msg.timestamp_
           << ")=\""
           << msg.data_ + msg.header_length ///< @todo Unsafe call to body!
           << "\"";
}

/**
 * Destroy this message and it's content.
 */
Message::~Message()
{
    delete[] data_;

    PRINT(this << " destroyed");
}

/**
 * Decode received header. Return TRUE if there is a body to read (bodylength > 0).
 * @pre A body has to be read before this function is useful.
 * @return There is a body to read
 */
bool Message::decode_header()
{
    char buffer[header_length + 2] = "";
    uint8_t type;

    std::strncat(buffer, data_, sizeof(type));

    type_ = atoi(buffer);
    buffer[0] = '\0';

    std::strncat(buffer, data_ + sizeof(type), sizeof(length_));

    length_ = atoi(buffer);
    buffer[0] = '\0';

    std::strncat(buffer, data_ + sizeof(type) + sizeof(length_), sizeof(timestamp_));

    timestamp_ = atoi(buffer);

    if (length_ > 0) {
        return true;
    }

    return false;
}

/**
 * Get length of message-body as specified in the header.
 * @pre Read a header from socket and called decode_header()
 * @return Length of body
 */
size_t Message::getLength() const
{
    return length_;
}

/**
 * This function can be used to get a buffer of this message for writing it to a Connection.
 * @pre Content of the Message has to be set by construction or setters.
 * @return Buffer of this message
 */
std::vector<asio::const_buffer> Message::toBuffers() const
{
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(asio::buffer(&type_, 1));
    buffers.push_back(asio::buffer(&length_, 2));
    buffers.push_back(asio::buffer(&timestamp_, 4));

    if ((type_ == 0x01) || (type_ == 0x02)) { ///< @todo Encode different headers
        buffers.push_back(asio::buffer(data_ + header_length, length_));
    }

    return buffers;
}

/**
 * The timestamp of this message. Either set on construction or by using setTimestamp().
 * @return Timestamp of message
 */
uint32_t Message::getTimestamp() const
{
    return timestamp_;
}

/**
 * Set the timestamp of the Message. The timestamp has to be set according to the specification depending on the
 * MessageType of Message.
 * @param time
 */
void Message::setTimestamp(uint32_t time)
{
    timestamp_ = time;
}

/**
 *
 * Get the MessageType of this Message. If no MessageType is set on creation and no decode_header() is called in
 * between, it is set to ERROR and the message should not be used further.
 * @return Type of Message
 */
MessageType Message::getType() const
{
    return IntToType(type_);
}

/**
 * Set the MessageType of this Message.
 * @param type MessageType of this Message
 */
void Message::setType(MessageType type)
{
    type_ = TypeToInt(type);
}

/**
 * Constructs a new Message and return a Message::pointer to it. This provides safe use of boost::shared_ptr.
 * @param type Type of the new Message
 * @param allocator Body of the new Message
 * @param timestamp Timestamp of the new Message
 * @return Smart-pointer to the new Message
 */
Message::pointer Message::createMessage(MessageType type, std::string allocator, uint32_t timestamp)
{
    return pointer(new Message(type, allocator, timestamp));
}

/**
 * Converts a given uint8_t to its MessageType equivalent.
 * @param unsignedChar The decimal representation
 * @return Corresponding MessageType
 */
MessageType Message::IntToType(uint8_t unsignedChar)
{
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

/**
 * Converts a given MessageType to its decimal equivalent.
 * @param messageTypeEnum The MessageType
 * @return integer Corresponding representation of MessageType
 */
uint8_t Message::TypeToInt(MessageType messageTypeEnum)
{
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

} /* namespace freejtag */

