/*
 ============================================================================
 Name        : freejtag.c
 Author      : Arne Wischer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "freejtag.h"
//#include "daemon.h"
#include "settings.h"

//#include <stdlib.h>
//#include <syslog.h>
//#include <time.h>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>

int main(int argc, char* argv[]) {
	freejtag::freejtag *prog;
	prog = new freejtag::freejtag(argc, argv);
	int res = prog->run();
	delete prog;
	return res;
}

namespace freejtag {
freejtag::freejtag(int argc, char* argv[]):prog_settings(argc,argv),
		prog_network(12323),
		uart_service_(prog_settings){
	PRINT("new freejtag");
	//prog_network = new NetworkService(message_queue_, 12323);
}
freejtag::~freejtag() {
}

int freejtag::run() {
	// check settings for daemon
	// po::variables_map map = prog_settings->get_map();
	// bool b = prog_settings->get_value<bool>("detached");
	if(prog_settings.get_value<bool>("detached") == true){
		PRINT("Detached");
		//init daemon
	}
	bool run = true;
	while (run) {
		// setup telnet
		// setup serial
		// do stuff
		// teardown

		PRINT("PING!");
		//Message msg = Message(PING);
		prog_network.sendBroadcast(Message::createMessage(MESS,"Test!"));
		//boost::thread telnet_thread(*prog_telnet::run());
		//prog_telnet->run();
		boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
	}
	return 0;
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
