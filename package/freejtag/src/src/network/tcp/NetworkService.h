/**
 * @file NetworkService.h
 * @date Jan 3, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef NETWORKSERVICE_H_
#define NETWORKSERVICE_H_

#include "ConnectionBundle.h"

namespace asio = boost::asio;

namespace freejtag{

/**
 * Manages network related TCP functions.
 * This class is in charge of everything related to the TCP networking. It needs a boost::io_service,
 * NetworkBuffer and port on startup. The io_service is used to create an acceptor and bind it to a
 * tcp::endpoint which will be created on the specified port. The method start_accept() needs to be called
 * to start accepting new connection. A broadcast can be send to all currently connected clients.
 * <br/>Examples used for creating this class:
 * <ul>
 * <li><a href="http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_server.cpp">
 * A simple chatserver</a></li>
 * <li><a href="http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html">
 * A simple daytime server</a></li></ul>
 */
class NetworkService{
private:
    NetworkBuffer& input_buffer_; ///< Buffer used to store incoming messages
    asio::io_service& io_service_; ///< Handles asynchronous networking
    asio::ip::tcp::acceptor accepto_; ///< Used for incoming connections
    Connection::pointer new_connection_; ///< Temporary storage for a new Connection
    ConnectionBundle connection_bundle_; ///< Stores all current Connection instances

    void handle_accept(Connection::pointer ptr, const boost::system::error_code& err);
public:
    NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, unsigned int port);
    void start_accept();
    void shutdown();
    void remove_connection(Connection::pointer conn);
    bool send_broadcast(Message::pointer msg);
    bool send_message(Connection::pointer conn, Message::pointer msg);
};

}

#endif /* NETWORKSERVICE_H_ */
