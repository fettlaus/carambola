/**
 * @file UARTConnection.cpp
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "UARTConnection.h"

namespace freejtag {

/**
 * Create a new UARTConnection instance.
 * The provided io_service will be used to handle all the asynchronous serial calls of this class. The
 * UARTBuffer stores multiple instances of UARTMessage.
 * @param io_service Service to use asynchronous methods with
 * @param buffer Buffer in which to store incoming serial messages
 * @see UARTMessage
 */
UARTConnection::UARTConnection(boost::asio::io_service& io_service, UARTBuffer& buffer):
        port_(io_service),
        buffer_(buffer),
        input_stream_(&stream_buffer_){
}

UARTConnection::~UARTConnection() { }

/**
 * Open a specific device.
 * The method opens the specified device. This can be for example /dev/ttyS0 on Linux. After opening
 * the device, the method starts a new asynchronous accept on it.
 * @param device The device that should be opened
 * @return Currently always true
 * @todo Return something useful
 */
bool UARTConnection::open(std::string device){
    port_.open(device);
    boost::asio::async_read_until(port_,stream_buffer_,'\n',
                    boost::bind(&UARTConnection::handle_read,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred)
    );
    return true;
}

boost::asio::serial_port& UARTConnection::get_port() {
    return this->port_;
}

void UARTConnection::close() {
    port_.close();
}

void UARTConnection::handle_read(const boost::system::error_code& ec,
        std::size_t size) {
    if(!ec){
        std::string new_string;
        std::getline(input_stream_,new_string);
        buffer_.push(std::make_pair(TimeKeeper::time().count(),new_string));
        //start new read
        boost::asio::async_read_until(port_,stream_buffer_,'\n',
                boost::bind(&UARTConnection::handle_read,
                        this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred)
        );
    }else{
        WARNING("Something went wrong at UART!");
    }
}

} /* namespace freejtag */
