/**
 * @file UARTService.h
 * @date Jan 11, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

#include "UARTConnection.h"

namespace freejtag {

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
    boost::asio::io_service& io_service_;
    bool shutdown_;
    UARTBuffer& uart_buffer_;
    UARTConnection uart_connection_;
    std::string device_;
};

/**
 * Set options on serial port.
 * @param opt Option to set
 * @param name Name for debug
 * @return
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
