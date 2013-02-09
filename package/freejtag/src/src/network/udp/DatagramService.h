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
    void stop_socket();
private:
    bool running_;
    void delay_tuner(microseconds delay);
    ip::udp::socket socket_;
    ip::udp::endpoint sender_endpoint_;
    Message::pointer cur_message_;
    microseconds t1, t2, t3, t4;
    enum {
        time_sync_buffer = 10, ///< How many syncs we need until adjusting time
        time_msec_direct = 90 ///< What is the maximum deviation until we directly set time
    };
};

} /* namespace freejtag */
#endif /* DATAGRAMSERVICE_H_ */
