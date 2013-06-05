/**
 * @file Connection.h
 * @date Dec 24, 2012
 * @author Arne Wischer <Fettlaus@gmail.com>
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "MessageTarget.h"
#include "ConnectionTypedef.h"
#include "ConnectionException.h"

#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

namespace freejtag {
/**
 * Class for a single Connection. An object of this class can be created by calling create_new().
 * This call returns a Connection::pointer which is used to access the object. After creation the
 * internal socket should be connected by an Acceptor to a single incoming connection. Once it is
 * connected, the Connection can be made active by Connection::start().
 */
class Connection: public MessageTarget, public boost::enable_shared_from_this<Connection> {
public:
    typedef boost::shared_ptr<Connection> pointer; ///< Shared pointer for a connection
    //typedef boost::error_info<struct tag_connection_info,Connection::pointer> connection_info;
    //struct connection_exception: virtual boost::exception, virtual std::exception { };

    ~Connection();
    static pointer create_new(NetworkBuffer& input_buffer, boost::asio::io_service& service);
    void deliver(const Message::pointer);
    boost::asio::ip::tcp::socket& get_socket();
    void start();
    void close();

private:
	boost::asio::ip::tcp::socket socket_; ///< The socket of this Connection
	Message::pointer cur_message_; ///< The message we are reading into
    NetworkBuffer& input_buffer_; ///< The buffer for incoming Messages
    boost::asio::io_service::strand strand_; ///< Strand to synchronize socket access

    Connection(NetworkBuffer& input_buffer, boost::asio::io_service& service);
    void handle_write(const boost::system::system_error& err, size_t, const Message::pointer msg);
    void handle_read_header(const boost::system::system_error& err);
    void handle_read_body(const boost::system::system_error& err);
};






} /* namespace freejtag */
#endif /* CONNECTION_H_ */
