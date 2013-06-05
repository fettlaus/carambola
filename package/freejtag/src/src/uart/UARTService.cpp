/**
 * @file UARTService.cpp
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "UARTService.h"

namespace freejtag {

UARTService::UARTService(boost::asio::io_service& io_service, UARTBuffer& buffer):
        shutdown_(false),
        uart_connection_(io_service_,buffer),
        io_service_(io_service),
        uart_buffer_(buffer){
}

UARTService::~UARTService() { }

void UARTService::reload_settings() {
    using namespace boost::asio;
    uart_connection_.close();
    uart_connection_.open(device_);
}

void UARTService::open(std::string device) {
    uart_connection_.open(device);
}

void UARTService::close(){
    uart_connection_.close();
}

} /* namespace freejtag */
