/**
 * @file UARTConnection.h
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef UARTCONNECTION_H_
#define UARTCONNECTION_H_

#include "UARTConnectionTypedef.h"

#include <boost/asio/read_until.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/streambuf.hpp>

namespace freejtag {

class UARTConnection {
public:
    UARTConnection(boost::asio::io_service& io_service, UARTBuffer& buffer);
    virtual ~UARTConnection();

    boost::asio::serial_port& get_port();
    bool open(std::string device);
    void close();
private:
    void handle_read(const boost::system::error_code& ec, std::size_t size);
    UARTBuffer& buffer_;
    boost::asio::io_service& io_service_;
    boost::asio::serial_port port_;
    boost::asio::streambuf stream_buffer_;
    std::istream input_stream_;
};

} /* namespace freejtag */
#endif /* UARTCONNECTION_H_ */
