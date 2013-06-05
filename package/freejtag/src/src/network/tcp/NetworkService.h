/**
 * @file NetworkService.h
 * @date Jan 3, 2013
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef TELNET_H_
#define TELNET_H_

#include "ConnectionBundle.h"

namespace asio = boost::asio;

namespace freejtag{

/**
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_server.cpp
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html
 */
class NetworkService{
private:
    NetworkBuffer& input_buffer_;
    asio::io_service& io_service_;
    asio::ip::tcp::acceptor accepto_;
    bool shutdown_;
    void handle_accept(Connection::pointer ptr, const boost::system::error_code& err);
    Connection::pointer new_connection_;
    MessageTargetBundle connection_bundle_;
public:
    void start_accept();
    void shutdown();
    NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, unsigned int port);
    void remove_connection(Connection::pointer conn);
    bool send_broadcast(Message::pointer msg);
    bool send_message(Connection::pointer conn, Message::pointer msg);
};

}

#endif /* TELNET_H_ */
