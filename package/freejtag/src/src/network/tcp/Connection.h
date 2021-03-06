/**
 * @file Connection.h
 * @date Dec 24, 2012
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "BaseConnection.h"
#include "MessageTarget.h"
#include "NetworkServiceTypedef.h"

#include <network/Message.h>

#include <boost/asio/strand.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace freejtag {

class Connection: public BaseConnection, public MessageTarget, public boost::enable_shared_from_this<Connection> {
private:
    Connection(NetworkBuffer& output_queue, boost::asio::io_service& service); ///< Hidden constructor
    Message::pointer cur_message_; ///< The message we are reading into
    void handle_write(const boost::system::system_error& err, size_t, const Message::pointer msg);
    void handle_read_header(const boost::system::system_error& err);
    void handle_read_body(const boost::system::system_error& err);
    NetworkBuffer& output_queue_;
    boost::mutex send_mutex_;
    boost::asio::io_service::strand strand_;
public:
    ~Connection();
    typedef boost::shared_ptr<Connection> pointer;
    static pointer create_new(NetworkBuffer& input_messages, boost::asio::io_service& service);
    void deliver(const Message::pointer);
    void start();
    void close();
};

} /* namespace freejtag */
#endif /* CONNECTION_H_ */
