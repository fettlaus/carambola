/*
 ============================================================================
 Name        : freejtag.c
 Author      : Arne Wischer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Freejtag.h"

//#include "daemon.h"
#include "settings.h"

#include <network/tcp/ConnectionException.h>

//#include <stdlib.h>
//#include <syslog.h>
//#include <time.h>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

int main(int argc, char* argv[]) {
    freejtag::Freejtag *prog;
    prog = new freejtag::Freejtag(argc, argv);
    int res = prog->run();
    delete prog;
    return res;
}

namespace freejtag {
Freejtag::Freejtag(int argc, char* argv[]) :
    prog_settings(argc, argv),
    prog_network(io_service_, input_network_, prog_settings),
    uart_service_(io_service_, input_uart_, prog_settings),
    uart_dispatcher_(boost::bind(&Freejtag::uart_handle, this)),
    network_dispatcher_(boost::bind(&Freejtag::network_handle, this)),
    udp_handler_(boost::bind(&DatagramService::start_socket, &prog_datagram_)),
    prog_datagram_(io_service_,prog_settings){
    PRINT("FreeJTAG set up ...");
    //prog_network = new NetworkService(message_queue_, 12323);
}
Freejtag::~Freejtag() {
}

void Freejtag::uart_handle() {
    while (true) {
        UARTMessage msg = input_uart_.pop();
        prog_network.sendBroadcast(Message::create_message(UART, msg.second, msg.first));
    }
}

void Freejtag::network_handle() {
    while (true) {
        MessageDatagram msgd = input_network_.pop();
        PRINT("Incoming Message!");
        Message::pointer msg = msgd.second;
        Connection::pointer con = msgd.first;
        MessageType type = msg->get_type();
        if (type == MESS) { ///< Echo MESS to everyone
            prog_network.sendBroadcast(msg);
        } else if (type == PING) { ///< Answer PING
            prog_network.sendMessage(con, Message::create_message(PONG));
        }
    }
}

int Freejtag::run() {
    prog_network.start_accept();
    //set serial options
    using namespace boost::asio;
    PRINT(prog_settings.get_value<std::string>("device"));
    uart_service_.open(prog_settings.get_value<std::string>("device"));
    uart_service_.set_setting<uart::parity>(prog_settings.get_value<uart::parity>("parity"), "parity");
    uart_service_.set_setting<uart::flow_control>(prog_settings.get_value<uart::flow_control>("flow_control"),
        "flow control");
    uart_service_.set_setting<uart::stop_bits>(prog_settings.get_value<uart::stop_bits>("stop_bits"), "stop bits");
    uart_service_.set_setting<serial_port::baud_rate>(
        serial_port::baud_rate(prog_settings.get_value<unsigned int>("baud")), "baud rate");
    uart_service_.set_setting<serial_port::character_size>(
        serial_port::character_size(prog_settings.get_value<unsigned int>("data")), "char size");

    // check settings for daemon
    // po::variables_map map = prog_settings->get_map();
    // bool b = prog_settings->get_value<bool>("detached");
    if (prog_settings.get_value<bool>("detached") == true) {
        PRINT("Detached");
        //init daemon
    }
    boost::asio::deadline_timer t(io_service_, boost::posix_time::seconds(5));
    t.async_wait(boost::bind(&Freejtag::ping, this, &t));
    bool run = true;
    while (run) {
        try {
            io_service_.run();
        } catch (boost::system::system_error& err) {
            WARNING("System Error");
        } catch (connection_exception& err) {
            PRINT("Disconnected Client!");
            if (Connection::pointer const * con = boost::get_error_info<connection_info>(err)) {
                prog_network.removeConnection(*con);
            }

        }
        // setup telnet
        // setup serial
        // do stuff
        // teardown
    }
    return 0;
}

void Freejtag::ping(boost::asio::deadline_timer* t) {
    t->expires_at(t->expires_at() + boost::posix_time::microsec(1000));
    prog_network.sendBroadcast(Message::create_message(MESS, "PING!"));
    t->async_wait(boost::bind(&Freejtag::ping, this, t));
}
}
/*
 gboolean nodetach = FALSE;

 static GOptionEntry options[] = { { "nodetach", 0, 0, G_OPTION_ARG_NONE,
 &nodetach, "disable detaching from parent process", NULL }, { NULL } };

 #ifdef DEBUG
 gboolean fj_heartbeat() {
 time_t t;
 struct tm* zeit;
 time(&t);
 zeit = localtime(&t);
 PRINT("Heartbeat at %02i:%02i:%02i",zeit->tm_hour,zeit->tm_min,zeit->tm_sec);
 return TRUE;
 }
 #endif

 int main2(int argc, char** args) {
 if (!GLIB_CHECK_VERSION(2, 26, 0)) {
 ERROR("Need GLib 2.26.0");
 }PRINT("GLib %i.%i.%i present", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);PRINT("Starting FreeJTAG w\\ Debug enabled.");
 g_type_init();
 GError* error = NULL;
 GOptionContext* context;
 context = g_option_context_new(NULL);
 g_option_context_set_summary(context, "FreeJTAG Debugging-Bridge");
 g_option_context_add_main_entries(context, options, NULL);

 if (!g_option_context_parse(context, &argc, &args, &error)) {
 ERROR("%s", error->message);
 exit(EXIT_FAILURE);
 }
 g_option_context_free(context);

 //Load configuration
 if (!fj_settings_load(NULL, &error)) {
 ERROR("Can't load configuration: %s", error->message);
 }

 //forking and starting daemon
 if (!nodetach) {
 fj_daemon_fork();
 }

 fj_daemon_init(0);

 //FreeJTAG Init
 syslog(LOG_INFO, "%s", "FreeJTAG startet successfully");

 //Main Loop
 GMainLoop* mainloop;
 mainloop = g_main_loop_new(NULL, FALSE);

 GThread* telnet;
 telnet = g_thread_new("telnet", (GThreadFunc) fj_telnet_run, mainloop);

 #ifdef DEBUG
 g_timeout_add_seconds(10,fj_heartbeat,NULL);
 #endif
 g_main_loop_run(mainloop);

 g_main_context_unref(g_main_loop_get_context(mainloop));
 g_main_loop_unref(mainloop);
 return EXIT_FAILURE;
 }
 */
