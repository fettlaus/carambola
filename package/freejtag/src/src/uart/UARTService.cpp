/**
 * @file UARTService.cpp
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "UARTService.h"

namespace freejtag {

UARTService::UARTService(boost::asio::io_service& io_service, UARTBuffer& buffer):
        uart_connection_(io_service,buffer),
        uart_buffer_(buffer){
}

UARTService::~UARTService() { }

/**
 * Reload settings. This method reloads the settings of current device after changing its options.
 * It does so by closing and reopening the device.
 * @todo Is this really useful?
 */
void UARTService::reload_settings() {
    using namespace boost::asio;
    uart_connection_.close();
    uart_connection_.open(device_);
}

/**
 * Open the specified device as connection. The specified device is something like /dev/ttyS0 on Linux.
 * @param device String representing the device
 */
void UARTService::open(std::string device) {
    uart_connection_.open(device);
}

/**
 * Close the current connection.
 */
void UARTService::close(){
    uart_connection_.close();
}

} /* namespace freejtag */
