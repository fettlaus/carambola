/*
 * telnet.c
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "NetworkService.h"
#include "Connection.h"
#include "ConnectionException.h"
#include <debug.h>
//#include "menu.h"

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

//#include <gio/gio.h>
//#include <glib.h>

// new mainloop
// new socketlistener
// attach_callback()
// on new connection:
// 		callback attaches watch and callback
// on server restart command:
// 		change port in cfg
//		close_connections()
//		attach_callback()
// on shutdown:
//		close_connections()
//		stop socketlistener
//		free resources
//
//
namespace freejtag {

NetworkService::NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, settings& settings) :
    io_service_(io_service),
    accepto(io_service_),
    shutdown_(false),
    settings_(settings),
    input_buffer_(buffer) {
    PRINT("new telnet");
    unsigned int this_port = settings.get_value<uint16_t>("port");
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), this_port);
    accepto.open(ep.protocol());
    accepto.set_option(boost::asio::socket_base::reuse_address(true));
    accepto.bind(ep);
    accepto.listen();
    start_accept();
    PRINT("Run Service");
}

void NetworkService::start_accept() {
    PRINT("Start accept");
    //asio::io_service& ios = accepto.get_io_service();
    Connection::pointer new_conn = Connection::create_new(input_buffer_, io_service_);
    accepto.async_accept(new_conn->get_socket(),
        boost::bind(&NetworkService::handle_accept, this, new_conn, asio::placeholders::error));
}
void NetworkService::handle_accept(Connection::pointer ptr, const boost::system::error_code& err) {
    PRINT("incoming Connection!");
    if (!err) {
        ptr->start();
        sendMessage(ptr, Message::create_message(MESS, "Hello, new connection!"));
    }
    connection_bundle_.addConnection(ptr);
    start_accept();
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
