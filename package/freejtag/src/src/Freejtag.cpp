/**
 * @file Freejtag.cpp
 * @date Dec 27, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "Freejtag.h"

#include "settings.h"

#include <network/tcp/ConnectionException.h>
#include <common/TimeKeeper.h>

#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

int main(int argc, char* argv[]) {
    freejtag::Freejtag *prog;
    prog = new freejtag::Freejtag(argc, argv);
    int res = prog->run();
    delete prog;
    return res;
}

namespace freejtag {
Freejtag::Freejtag(int argc, char* argv[]) :
    prog_settings(argc, argv),
    prog_network(io_service_, input_network_, prog_settings),
    uart_service_(io_service_, input_uart_, prog_settings),
    uart_dispatcher_(boost::bind(&Freejtag::uart_handle, this)),
    network_dispatcher_(boost::bind(&Freejtag::network_handle, this)),
    udp_handler_(boost::bind(&DatagramService::start_socket, &prog_datagram_)),
    prog_datagram_(io_service_,prog_settings),
    ping_timer_(io_service_, boost::posix_time::seconds(1)),
    running_(true){
    PRINT("FreeJTAG set up ...");
}
Freejtag::~Freejtag() {
}

void Freejtag::uart_handle() {
    while (running_) {
        UARTMessage msg = input_uart_.pop();
        prog_network.sendBroadcast(Message::create_message(UART, msg.second, msg.first));
    }
}

void Freejtag::network_handle() {
    while (running_) {
        MessageDatagram msgd = input_network_.pop();
        PRINT("Incoming Message!");
        Message::pointer msg = msgd.second;
        Connection::pointer con = msgd.first;
        MessageType type = msg->get_type();
        if (type == MESS) { ///< Echo MESS to everyone
            msg->set_timestamp(TimeKeeper::time().count());
            prog_network.sendBroadcast(msg);
        } else if (type == PING) { ///< Answer PING
            prog_network.sendMessage(con, Message::create_message(PONG));
        } else if (type == EXIT) {
            running_ = false;
            ping_timer_.cancel();
            prog_network.shutdown();
            uart_service_.close();
            prog_datagram_.stop_socket();
        }
    }
}

int Freejtag::run() {
    prog_network.start_accept();
    //set serial options
    using namespace boost::asio;
    PRINT(prog_settings.get_value<std::string>("uart.device"));
    uart_service_.open(prog_settings.get_value<std::string>("uart.device"));
    uart_service_.set_setting<uart::parity>(prog_settings.get_value<uart::parity>("uart.parity"), "parity");
    uart_service_.set_setting<uart::flow_control>(prog_settings.get_value<uart::flow_control>("uart.flow_control"),
        "flow control");
    uart_service_.set_setting<uart::stop_bits>(prog_settings.get_value<uart::stop_bits>("uart.stop_bits"), "stop bits");
    uart_service_.set_setting<serial_port::baud_rate>(
        serial_port::baud_rate(prog_settings.get_value<unsigned int>("uart.baud")), "baud rate");
    uart_service_.set_setting<serial_port::character_size>(
        serial_port::character_size(prog_settings.get_value<unsigned int>("uart.data")), "char size");

    unsigned int timeout = prog_settings.get_value<unsigned int>("common.ping");
    if(timeout > 0){
        ping_timer_.async_wait(boost::bind(&Freejtag::ping, this, boost::asio::placeholders::error, &ping_timer_, timeout));
    }
    while (running_) {
        try {
            io_service_.run();
            PRINT("Shutdown completed...");

        } catch (boost::system::system_error& err) {
            WARNING("System Error");
        } catch (connection_exception& err) {
            PRINT("Disconnected Client!");
            if (Connection::pointer const * con = boost::get_error_info<connection_info>(err)) {
                prog_network.removeConnection(*con);
            }

        }
    }
    network_dispatcher_.interrupt();
    network_dispatcher_.join();
    PRINT("Network joined");
    uart_dispatcher_.interrupt();
    uart_dispatcher_.join();
    PRINT("UART joined");
    udp_handler_.interrupt();
    udp_handler_.interrupt();
    udp_handler_.interrupt();
    udp_handler_.join();
    PRINT("ekit");
    return 0;
}

void Freejtag::ping(const boost::system::error_code& err,boost::asio::deadline_timer* t, unsigned int timeout) {
    if(running_){
        t->expires_at(t->expires_at() + boost::posix_time::microsec(timeout));
        prog_network.sendBroadcast(Message::create_message(MESS, "PING!"));
        t->async_wait(boost::bind(&Freejtag::ping, this, err, t, timeout));
    }else{
        PRINT("Cancel timer");
    }
}

}
