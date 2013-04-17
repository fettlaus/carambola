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

DatagramService::DatagramService(boost::asio::io_service& io_service, settings& settings) :
    socket_(io_service),
    running_(true),
    sequence_(0) {
    unsigned int this_port = settings.get_value<unsigned int>("port");
    ip::udp::endpoint ep(ip::udp::v4(), this_port);
    socket_.open(ep.protocol());
    socket_.bind(ep);
    cur_message_ = Message::create_message();
    PRINT("UDP set up ...");
}

/**
 * Close this socket. Will automatically call the handlers with an error code if they are still waiting.
 */
void DatagramService::stop_socket() {
    running_ = false;
    socket_.close();
}

/**
 * Start socket to listen for UDP packages.
 */
void DatagramService::start_socket() {
    PRINT("Start UDP Listening");
    socket_.async_receive_from(boost::asio::buffer(cur_message_->get_header(), Message::udp_packet_length),
        sender_endpoint_, boost::bind(&DatagramService::handle_read, this, boost::asio::placeholders::error));
}

/**
 * This function accumulates some delays and adjusts the TimeKeeper after gathering some.
 * It will also directly adjust the Timekeeper if a delay is greater than time_msec_direct.
 * @param delay
 */
void DatagramService::delay_tuner(microseconds delay) {
    static microseconds buf[time_sync_buffer];
    static int next_index = 0;
    if (delay > microseconds(time_msec_direct) || delay < microseconds(-time_msec_direct)) {
        TimeKeeper::set(delay);
    } else {
        buf[next_index] = delay;
        next_index++;
        if (next_index >= time_sync_buffer) {
            microseconds accu(0);
            for (int i = 0; i < next_index; i++) {
                PRINT("Delay "<< i << " is "<<buf[i]);
                accu = accu + buf[i];
            }
            accu = accu / (next_index);
            TimeKeeper::set(accu);
            next_index = 0;
        }
    }

}

/**
 * Handle received UDP package. This function will check the Type of message and act depending on it.
 * If we received a MessageType::PING Message, we will set the sequence number, get the needed timepoints and send
 * a PONG back.
 * If we received a MessageType::STIM, we will check the sequence number, calculate the result and send it to
 * DatagramService::delay_tuner().
 * @pre DatagramService::start_socket() has been called
 * @param err
 */
void DatagramService::handle_read(const boost::system::system_error& err) {
    microseconds tmp = TimeKeeper::time();
    if (err.code() == 0) {
        int body_length = cur_message_->decode_header();
        MessageType t = cur_message_->get_type();
        if (t == PING) {
            t2 = tmp;
            t1 = microseconds(cur_message_->get_timestamp());
            sequence_ = cur_message_->get_timestamp();
            cur_message_->set_type(PONG);
            std::vector<const_buffer> buf = cur_message_->to_buffers();
            t3 = TimeKeeper::time();
            socket_.async_send_to(buf, sender_endpoint_,
                boost::bind(&DatagramService::handle_write, this, placeholders::error,
                    placeholders::bytes_transferred));
        } else {
            if (body_length > 0 && t == STIM) {
                if (sequence_ == cur_message_->get_timestamp()) {
                    t4 = microseconds(cur_message_->get_payload());
                    microseconds delay((t2 - t1 - t4 + t3) / 2);
                    delay_tuner(delay);
                }
            }
            socket_.async_receive_from(boost::asio::buffer(cur_message_->get_header(), Message::udp_packet_length),
                sender_endpoint_, boost::bind(&DatagramService::handle_read, this, boost::asio::placeholders::error));

        }
    }
}

/**
 * Start a new read if no error occured.
 * @param err
 * @param bytes_written
 */
void DatagramService::handle_write(const boost::system::system_error& err, size_t bytes_written) {
    if (err.code() == 0) {
        socket_.async_receive_from(boost::asio::buffer(cur_message_->get_header(), Message::udp_packet_length),
            sender_endpoint_, boost::bind(&DatagramService::handle_read, this, boost::asio::placeholders::error));
    }
}

DatagramService::~DatagramService() { }

} /* namespace freejtag */
