/**
 * @file DatagramService.h
 * @date Feb 7, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef DATAGRAMSERVICE_H_
#define DATAGRAMSERVICE_H_

#include <network/Message.h>

#include <boost/bind/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/ip/udp.hpp>

namespace freejtag {
using namespace boost::asio;
using namespace boost::chrono;

/**
 * This class handles UDP communication.
 * It is used for adjustment of the TimeKeeper. Therefore it asynchronously reads from its socket into
 * a Message instance which parses the information.<p/>
 * For calculation of the difference between the server and a client we need four points in time and three
 * messages to transmit them:
 * <ul><li>t1: PING-message sent by client</li>
 * <li>t2: PING-message received by server</li>
 * <li>t3: PONG-message sent by server</li>
 * <li>t4: PONG-message received by client</li></ul>
 * Following this logic, the server already knows three out of these four points. A third STIM-message
 * is used to transmit the fourth timestamp back to the server.<p/>
 * After this sequence, we can calculate the difference by this equation: <b>(t2 - t1 - t4 + t3) / 2</b>
 * <p/>Because the four important timestamps are transported in the body of the messages, the actual timestamp
 * fields of all messages in a single sequence are identical which effectively makes it a sequence
 * number that equals the first transmitted timestamp t1. This ensures, that only matching messages are
 * accepted into the calculation.
 * @see TimeKeeper
 */
class DatagramService {
public:
    DatagramService(io_service& io_service, unsigned int port);
    void start_socket();
    void stop_socket();
private:
    void handle_read(const boost::system::system_error& err);
    void handle_write(const boost::system::system_error& err, size_t bytes_written);
    void delay_tuner(microseconds delay);
    ip::udp::socket socket_; ///< Unconnected datagram socket
    ip::udp::endpoint sender_endpoint_; ///< Used to store the sender of a received datagram
    Message::pointer cur_message_; ///< The last read datagram
    microseconds t1_, t2_, t3_, t4_; ///< Used for calculation of the difference
    Message::MessageTimestamp sequence_; ///< Used for storage of the sequence number
    enum {
        time_sync_buffer = 10, ///< How many syncs we need until adjusting time
        time_msec_direct = 90 ///< What is the maximum deviation until we directly set time
    };
};

} /* namespace freejtag */
#endif /* DATAGRAMSERVICE_H_ */
