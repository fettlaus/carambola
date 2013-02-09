/**
 * @file DatagramService.h
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef DATAGRAMSERVICE_H_
#define DATAGRAMSERVICE_H_

#include <network/Message.h>

#include <boost/thread.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/chrono.hpp>
#include <settings.h>

namespace freejtag {
using namespace boost::asio;
using namespace boost::chrono;
/**
 *
 */
class DatagramService {
public:
    DatagramService(io_service& io_service, settings& settings);
    virtual ~DatagramService();
    void start_socket();
private:
    void handle_message(const boost::system::system_error& err);
    void handle_send(const boost::system::system_error& err, size_t bytes, Message::pointer msg);
    ip::udp::socket socket_;
    ip::udp::endpoint sender_endpoint_;
    char data[Message::header_length];
    boost::thread udp_handler_;
    Message::pointer cur_message_;
    microseconds t1;
    microseconds t2;
    microseconds t2_prev;
    microseconds t3;
    microseconds t4;
};

} /* namespace freejtag */
#endif /* DATAGRAMSERVICE_H_ */
