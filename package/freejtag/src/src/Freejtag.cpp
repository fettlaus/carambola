/**
 * @file Freejtag.cpp
 * @date Dec 27, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "Freejtag.h"

int main(int argc, char* argv[]) {
    freejtag::Freejtag *prog;
    prog = new freejtag::Freejtag(argc, argv);
    int res = prog->run();
    delete prog;
    return res;
}

namespace freejtag {
Freejtag::Freejtag(int argc, char* argv[]) :
    prog_settings_(argc, argv),
    prog_network_(io_service_, input_network_, prog_settings_.get_value<unsigned int>("port")),
    uart_service_(io_service_, input_uart_),
    uart_dispatcher_(boost::bind(&Freejtag::uart_handle, this)),
    network_dispatcher_(boost::bind(&Freejtag::network_handle, this)),
    prog_datagram_(io_service_,prog_settings_.get_value<unsigned int>("port")),
    ping_timer_(io_service_, boost::posix_time::seconds(1)),
    running_(true){
    PRINT("FreeJTAG set up ...");
}
Freejtag::~Freejtag() {
}

void Freejtag::uart_handle() {
    while (running_) {
        UARTMessage msg = input_uart_.pop();
        prog_network_.send_broadcast(Message::create_message(Message::UART, msg.second, msg.first));
    }
}

void Freejtag::network_handle() {
    while (running_) {
        MessageDatagram msgd = input_network_.pop();
        PRINT("Incoming Message!");
        Message::pointer msg = msgd.second;
        Connection::pointer con = msgd.first;
        Message::Type type = msg->get_type();
        if (type == Message::MESS) { ///< Echo MESS to everyone
            msg->set_timestamp(TimeKeeper::time().count());
            prog_network_.send_broadcast(msg);
        } else if (type == Message::PING) { ///< Answer PING
        	con->deliver(Message::create_message(Message::PONG));
        } else if (type == Message::EXIT) {
            running_ = false;
            ping_timer_.cancel();
            prog_network_.shutdown();
            uart_service_.close();
            prog_datagram_.stop_socket();
        }
    }
}

int Freejtag::run() {
    prog_network_.start_accept();
    prog_datagram_.start_socket();
    //set serial options
    using namespace boost::asio;
    PRINT(prog_settings_.get_value<std::string>("device"));
    uart_service_.open(prog_settings_.get_value<std::string>("device"));
    uart_service_.set_setting<uart::parity>(prog_settings_.get_value<uart::parity>("parity"), "parity");
    uart_service_.set_setting<uart::flow_control>(prog_settings_.get_value<uart::flow_control>("flow_control"),
        "flow control");
    uart_service_.set_setting<uart::stop_bits>(prog_settings_.get_value<uart::stop_bits>("stop_bits"), "stop bits");
    uart_service_.set_setting<serial_port::baud_rate>(
        serial_port::baud_rate(prog_settings_.get_value<unsigned int>("baud")), "baud rate");
    uart_service_.set_setting<serial_port::character_size>(
        serial_port::character_size(prog_settings_.get_value<unsigned int>("data")), "char size");

    unsigned int timeout = prog_settings_.get_value<unsigned int>("ping");
    if(timeout > 0){
        ping_timer_.async_wait(boost::bind(&Freejtag::ping, this, boost::asio::placeholders::error, &ping_timer_, timeout));
    }
    while (running_) {
        try {
            io_service_.run();
            PRINT("Shutdown completed...");

        } catch (boost::system::system_error& err) {
            WARNING("System Error");
        } catch (ConnectionException& err) {
            PRINT("Disconnected Client!");
            if (Connection::pointer const * con = boost::get_error_info<ConnectionInfo>(err)) {
                prog_network_.remove_connection(*con);
            }

        }
    }
    network_dispatcher_.interrupt();
    network_dispatcher_.join();
    PRINT("Network joined");
    uart_dispatcher_.interrupt();
    uart_dispatcher_.join();
    PRINT("UART joined");
    PRINT("Exit");
    return 0;
}

void Freejtag::ping(const boost::system::error_code& err,boost::asio::deadline_timer* t, unsigned int timeout) {
    if(running_){
        t->expires_at(t->expires_at() + boost::posix_time::microsec(timeout));
        prog_network_.send_broadcast(Message::create_message(Message::MESS, "PING!"));
        t->async_wait(boost::bind(&Freejtag::ping, this, err, t, timeout));
    }else{
        PRINT("Cancel timer");
    }
}

}
