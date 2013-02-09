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
    running_(true) {
    unsigned int this_port = settings.get_value<uint16_t>("port");
    ip::udp::endpoint ep(ip::udp::v4(), this_port);
    socket_.open(ep.protocol());
    socket_.bind(ep);
    PRINT("UDP set up ...");
}

void DatagramService::stop_socket() {
    running_ = false;
    socket_.shutdown(socket_base::shutdown_both);
    socket_.close();
}

void DatagramService::start_socket() {
    PRINT("UDP running");
    cur_message_ = Message::create_message();
    while (running_) {
        try {
            socket_.receive_from(buffer(cur_message_->get_header(), cur_message_->header_length), sender_endpoint_);
            t2 = TimeKeeper::time();
            cur_message_->decode_header();
            if (cur_message_->get_type() != PING) {
                continue;
            }
            t1 = microseconds(cur_message_->get_timestamp());
            cur_message_->set_type(PONG);
            cur_message_->set_timestamp(TimeKeeper::time().count());
            std::vector<const_buffer> buf = cur_message_->to_buffers();
            t3 = TimeKeeper::time();
            socket_.send_to(buf, sender_endpoint_);
            socket_.receive_from(buffer(cur_message_->get_header(), cur_message_->header_length), sender_endpoint_);
            cur_message_->decode_header();
            if (cur_message_->get_type() != STIM) {
                continue;
            }
            t4 = microseconds(cur_message_->get_timestamp());
            microseconds delay((t2 - t1 - t4 + t3) / 2);
            delay_tuner(delay);
            //PRINT("T1: "<< t1 <<'\n' <<"T2: "<< t2 <<'\n'<<"T3: "<< t3 <<'\n'<<"T4: "<< t4);
            //TimeKeeper::set(delay);

        } catch (boost::system::system_error& err) {
            PRINT("UDP-Error");
            continue;
        }
    }
    PRINT("UDP shutdown");
}

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

DatagramService::~DatagramService() {
    ///<  @todo Auto-generated destructor stub
}

} /* namespace freejtag */
