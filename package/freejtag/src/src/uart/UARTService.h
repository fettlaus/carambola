/**
 * @file UARTService.h
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

#include "UARTConnection.h"

namespace freejtag {

/**
 * This class handle UART communication.
 * It is used for configuring the serial port and reading data from it. a UARTBuffer and an io_service
 * have to be provided. The buffer is used to hold received data and should continuously be read by
 * another thread. After opening the desired port by calling open(), the port should be configured
 * by using the set_setting() method.
 */
class UARTService {
public:
    UARTService(boost::asio::io_service& io_service, UARTBuffer& buffer);
    virtual ~UARTService();
    void open(std::string device);
    void close();
    template<typename SettableSerialPortOption>
    void set_setting(const SettableSerialPortOption& option, std::string name);

private:
    void reload_settings();
    UARTBuffer& uart_buffer_; ///< Stores received messages
    UARTConnection uart_connection_; ///< The actual connection
    std::string device_; ///< String representation of the device
};

/**
 * Set options on serial port.
 * @param opt Option to set
 * @param name Name for debug
 * @todo Improve encapsulation: Do we really need a method like this?
 */
template<typename SettableSerialPortOption>
void UARTService::set_setting(const SettableSerialPortOption& opt, std::string name) {
    try{
        uart_connection_.get_port().set_option(opt);
    }catch(boost::system::system_error& se){
        WARNING("UART: "<< se.what()<<". Invalid \""<< name <<"\"");
    }
}

} /* namespace freejtag */

#endif /* UARTSERVICE_H_ */
