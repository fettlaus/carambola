/*
 * Connection.h
 *
 *  Created on: Dec 24, 2012
 *      Author: fettlaus
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Message.h"
#include "BaseConnection.h"
#include "MessageTarget.h"

#include "NetworkServiceTypedef.h"

#include <boost/enable_shared_from_this.hpp>

//class boost::asio::io_service;
namespace freejtag {

//class MessageDatagramQueue;

class Connection: public BaseConnection, public MessageTarget, public boost::enable_shared_from_this<Connection> {
private:
    Connection(NetworkBuffer& output_queue, boost::asio::io_service& service); ///< Hidden constructor
    Message::pointer cur_message_; ///< The message we are reading into
    void handle_write(const boost::system::system_error& err, size_t, const Message::pointer msg);
    void handle_read_header(const boost::system::system_error& err);
    void handle_read_body(const boost::system::system_error& err);
    NetworkBuffer& output_queue_;
    boost::mutex send_mutex_;
public:
    ~Connection();
    typedef boost::shared_ptr<Connection> pointer;
    static pointer create_new(NetworkBuffer& input_messages, boost::asio::io_service& service);
    void deliver(const Message::pointer);
    void start();

    //bool send(const Message& msg);
    //void connect_bindings();

};

} /* namespace freejtag */
#endif /* CONNECTION_H_ */
