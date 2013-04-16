/**
 * @file NetworkService.cpp
 * @date Jan 3, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "NetworkService.h"
#include "Connection.h"
#include "ConnectionException.h"
#include <debug.h>

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

namespace freejtag {

NetworkService::NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, settings& settings) :
    io_service_(io_service),
    accepto(io_service_),
    shutdown_(false),
    settings_(settings),
    input_buffer_(buffer) {
    unsigned int this_port = settings.get_value<unsigned int>("network.port");
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), this_port);
    accepto.open(ep.protocol());
    accepto.set_option(boost::asio::socket_base::reuse_address(true));
    accepto.bind(ep);
    accepto.listen();
    PRINT("TCP set up ...");
}

void NetworkService::start_accept() {
    PRINT("Start accept");
    new_connection_ = Connection::create_new(input_buffer_, io_service_);
    accepto.async_accept(new_connection_->get_socket(),
        boost::bind(&NetworkService::handle_accept, this, new_connection_, asio::placeholders::error));
}

void NetworkService::shutdown(){
    PRINT("Shutting down network");
    accepto.close();
    connection_bundle_.close_all_connections();
}

void NetworkService::handle_accept(Connection::pointer ptr, const boost::system::error_code& err) {
    if (err == 0) {
        PRINT("Incoming Connection!");
        ptr->start();
        sendMessage(ptr, Message::create_message(MESS, "Hello, new connection!"));
        connection_bundle_.addConnection(ptr);
        start_accept();
    } else {
        PRINT("Acceptor Error");
    }
}

bool NetworkService::sendBroadcast(Message::pointer msg) {
    PRINT("Got Broadcast!");
    connection_bundle_.sendBroadcast(msg);
    return true;
}

void NetworkService::removeConnection(Connection::pointer conn) {
    connection_bundle_.removeConnection(conn);
}

bool NetworkService::sendMessage(Connection::pointer ptr, Message::pointer msg) {
    PRINT("Got Direct-Message!");
    ptr->deliver(msg);
    return true;
}

}
