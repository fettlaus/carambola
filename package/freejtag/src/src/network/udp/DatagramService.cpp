/**
 * @file DatagramService.cpp
 * @date Feb 7, 2013
 * @author Arne Wischer<Fettlaus@gmail.com>
 */

#include "DatagramService.h"

#include <common/TimeKeeper.h>
#include <debug.h>

#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

namespace freejtag {

DatagramService::DatagramService(boost::asio::io_service& io_service, settings& settings):
    socket_(io_service),
    udp_handler_(boost::bind(&DatagramService::start_socket,this)) {
    ///< @todo Auto-generated constructor stub
    unsigned int this_port = settings.get_value<uint16_t>("port");
    ip::udp::endpoint ep(ip::udp::v4(),this_port);
    socket_.open(ep.protocol());
    socket_.bind(ep);

}

void DatagramService::start_socket(){
    while(true){
        cur_message_ = Message::create_message();
        try{
            socket_.receive_from(buffer(cur_message_->get_header(),cur_message_->header_length),
                    sender_endpoint_);
            PRINT("Got PING");
            t2 = TimeKeeper::time();
            cur_message_->decode_header();
            if(cur_message_->get_type() != PING){
                continue;
            }
            t1 = microseconds(cur_message_->get_timestamp());
            Message::pointer msg = Message::create_message(PONG,"",TimeKeeper::time().count());
            std::vector<const_buffer> buf = cur_message_->to_buffers();
            t3 = TimeKeeper::time();
            socket_.send_to(msg->to_buffers(),
                            sender_endpoint_);
            PRINT("Sent PONG");
            socket_.receive_from(buffer(cur_message_->get_header(),cur_message_->header_length),
                                sender_endpoint_);
            cur_message_->decode_header();
            if(cur_message_->get_type() != STIM){
                continue;
            }
            PRINT("Got STIM");
            t4 = microseconds(cur_message_->get_timestamp());
            microseconds delay((t2-t1-t4+t3)/2);
            PRINT(delay);

        }catch(boost::system::system_error& err){
            PRINT("UDP-Error");
            continue;
        }
    }


    /*
     * , boost::bind(&DatagramService::handle_message,this,placeholders::error)
     */
}

void DatagramService::handle_message(const boost::system::system_error& err){
    t2_prev = t2;
    t2 = TimeKeeper::time();
    // timestamp
    if (!err.code()) {
        cur_message_->decode_header();
        if(cur_message_->get_type() == PING){

            // construct PONG
            Message::pointer msg = Message::create_message(PONG,"",TimeKeeper::time().count());
            //boost::asio::const_buffer& buf(msg->to_buffers());
            //buf = ;
            t3 = TimeKeeper::time();
            socket_.send_to(msg->to_buffers(),
                sender_endpoint_);
            /*
            boost::bind(&DatagramService::handle_send,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred,
                                msg)
            */
            // timestamp

            // send PONG
        }else if(cur_message_->get_type() == STIM){
            // check timeouts
            // calc difference
            // adjust TimeKeeper
        }

    }else{
        // TODO reset socket
    }

    socket_.async_receive_from(buffer(cur_message_->get_header(),cur_message_->header_length),
        sender_endpoint_,
        boost::bind(&DatagramService::handle_message,this,placeholders::error));
}

void DatagramService::handle_send(const boost::system::system_error& err, size_t bytes, Message::pointer msg){

}

DatagramService::~DatagramService() {
    ///<  @todo Auto-generated destructor stub
}

} /* namespace freejtag */
