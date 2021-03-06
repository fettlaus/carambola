/**
 * @file NetworkService.h
 * @date Jan 3, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef TELNET_H_
#define TELNET_H_

#include "Connection.h"

#include "MessageTargetBundle.h"
#include "NetworkServiceTypedef.h"

#include <settings.h>

#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <set>

namespace asio = boost::asio;

namespace freejtag{

/**
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/example/chat/chat_server.cpp
 * http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html
 */
class NetworkService{
private:
    NetworkBuffer& input_buffer_;
    settings& settings_;
    asio::io_service& io_service_;
    asio::ip::tcp::acceptor accepto;
    bool shutdown_;
    void handle_accept(Connection::pointer ptr, const boost::system::error_code& err);
    Connection::pointer new_connection_;
    MessageTargetBundle connection_bundle_;
public:
    void start_accept();
    void shutdown();
    NetworkService(asio::io_service& io_service, NetworkBuffer& buffer, settings& settings);
    void removeConnection(Connection::pointer conn);
    bool sendBroadcast(Message::pointer msg);
    bool sendMessage(Connection::pointer conn, Message::pointer msg);
};

}

#endif /* TELNET_H_ */
