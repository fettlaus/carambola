/**
 * @file NetworkService.cpp
 * @date Jan 3, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "NetworkService.h"

namespace freejtag {

NetworkService::NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, unsigned int port) :
    io_service_(io_service),
    accepto_(io_service_),
    shutdown_(false),
    input_buffer_(buffer) {
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), port);
    accepto_.open(ep.protocol());
    accepto_.set_option(boost::asio::socket_base::reuse_address(true));
    accepto_.bind(ep);
    accepto_.listen();
    PRINT("TCP set up ...");
}

void NetworkService::start_accept() {
    PRINT("Start accept");
    new_connection_ = Connection::create_new(input_buffer_, io_service_);
    accepto_.async_accept(new_connection_->get_socket(),
        boost::bind(&NetworkService::handle_accept, this, new_connection_, asio::placeholders::error));
}

void NetworkService::shutdown(){
    PRINT("Shutting down network");
    accepto_.close();
    connection_bundle_.close_all_connections();
}

void NetworkService::handle_accept(Connection::pointer ptr, const boost::system::error_code& err) {
    if (err == 0) {
        PRINT("Incoming Connection!");
        ptr->start();
        send_message(ptr, Message::create_message(Message::MESS, "Hello, new connection!"));
        connection_bundle_.add_connection(ptr);
        start_accept();
    } else {
        PRINT("Acceptor Error");
    }
}

bool NetworkService::send_broadcast(Message::pointer msg) {
    PRINT("Got Broadcast!");
    connection_bundle_.send_broadcast(msg);
    return true;
}

void NetworkService::remove_connection(Connection::pointer conn) {
    connection_bundle_.remove_connection(conn);
}

bool NetworkService::send_message(Connection::pointer ptr, Message::pointer msg) {
    PRINT("Got Direct-Message!");
    ptr->deliver(msg);
    return true;
}

}
