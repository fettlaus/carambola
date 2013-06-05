/**
 * @file Freejtag.h
 * @date Dec 27, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef FREEJTAG_H_
#define FREEJTAG_H_

#include "settings.h"

#include <network/tcp/NetworkService.h>
#include <network/udp/DatagramService.h>
#include <uart/UARTService.h>

#include <boost/thread/thread.hpp>
#include <boost/asio/deadline_timer.hpp>

namespace freejtag {
class Freejtag {
private:
    bool running_;
    boost::asio::io_service io_service_;
    UARTBuffer input_uart_;
    NetworkBuffer input_network_;
    settings prog_settings_;
    NetworkService prog_network_;
    DatagramService prog_datagram_;
    UARTService uart_service_;
    boost::thread uart_dispatcher_;
    boost::thread network_dispatcher_;
    boost::asio::deadline_timer ping_timer_;
    void ping(const boost::system::error_code& err, boost::asio::deadline_timer* t, unsigned int timeout);
    void uart_handle();
    void network_handle();

public:
    Freejtag(int argc, char* argv[]);
    ~Freejtag();
    int run();
};
}

#endif /* FREEJTAG_H_ */
