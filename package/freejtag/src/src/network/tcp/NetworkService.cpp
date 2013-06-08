/**
 * @file NetworkService.cpp
 * @date Jan 3, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#include "NetworkService.h"

namespace freejtag {

/**
 * Create a new NetworkService instance. This constructor also creates a new acceptor for accepting TCP
 * connections. It will be connected to a TCPv4 endpoint on the specified port.
 * @param io_service The connection service handling all asio related functions
 * @param buffer A buffer in which incoming Messages will be stored
 * @param port The TCP port on which new connections will be accepted
 */
NetworkService::NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, unsigned int port) :
    io_service_(io_service),
    accepto_(io_service_),
    input_buffer_(buffer) {
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), port);
    accepto_.open(ep.protocol());
    accepto_.set_option(boost::asio::socket_base::reuse_address(true));
    accepto_.bind(ep);
    accepto_.listen();
    PRINT("TCP set up ...");
}

/**
 * Start accepting new connections. This method creates a new Connection with a new socket first. The
 * socket of this new Connection will be used asynchronously by the acceptor for connecting a new Client.
 * Once a new connection is established, the asynchronous accept calls the handle_accept() method.
 */
void NetworkService::start_accept() {
    PRINT("Start accept");
    new_connection_ = Connection::create_new(input_buffer_, io_service_);
    accepto_.async_accept(new_connection_->get_socket(),
        boost::bind(&NetworkService::handle_accept, this, new_connection_, asio::placeholders::error));
}

/**
 * Closes the acceptor and all Connection instances. This method is mainly used on shutdown of the program.
 */
void NetworkService::shutdown(){
    PRINT("Shutting down network");
    accepto_.close();
    connection_bundle_.close_all_connections();
}

/**
 * This method gets called by the asynchronous accept. It will be called after a new connection on the port
 * of the Connection was opened. The method starts the new Connection, delivers a Message to all current
 * Connection instances and adds the new Connection to the internal storage. A new start_accept() will be
 * called afterwards.
 * If an Error occured, no new start_accept() will be called. This will also be called on shutdown of
 * the acceptor.
 * @todo Handle errors better
 * @param ptr The Connection of the newly connected socket
 * @param err contains an Error if an error occured during accept
 */
void NetworkService::handle_accept(Connection::pointer ptr, const boost::system::error_code& err) {
    if (err == 0) {
        PRINT("Incoming Connection!");
        ptr->start();
        ptr->deliver(Message::create_message(Message::MESS, "Hello, new connection!"));
        connection_bundle_.add_connection(ptr);
        start_accept();
    } else {
        PRINT("Acceptor Error");
    }
}

/**
 * Send a broadcast to all Connection instances.
 * @param msg The message to be delivered
 * @return currently always true
 * @todo Should return state of success or failure.
 */
bool NetworkService::send_broadcast(Message::pointer msg) {
    PRINT("Got Broadcast!");
    connection_bundle_.send_broadcast(msg);
    return true;
}

/**
 * Close and remove a single Connection. This method closes a Connection and removes it from the internal
 * storage. This method should be called, if a connection has to be closed.
 * @param conn The Connection to be closed
 */
void NetworkService::remove_connection(Connection::pointer conn) {
    connection_bundle_.remove_connection(conn);
}

/**
 * Send a Message to a given Connection. This method is used to encapsule access to the Connection.
 * @deprecated Since there are no other measures of encapsulation, this method is deprecated. Also the
 * returning bool isn't currently used.
 * @param ptr shared_ptr pointing to the target Connection
 * @param msg shared_ptr pointing to the Message
 * @return currently always true. Should return state of success or failure.
 */
bool NetworkService::send_message(Connection::pointer ptr, Message::pointer msg) {
    PRINT("Got Direct-Message!");
    ptr->deliver(msg);
    return true;
}

}
