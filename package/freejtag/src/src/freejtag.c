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
#include "daemon.h"
#include "settings.h"
#include "telnet.h"
#include <glib.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>

gboolean nodetach = FALSE;

static GOptionEntry options[] = {
		{"nodetach",0,0,G_OPTION_ARG_NONE,&nodetach,"disable detaching from parent process",NULL},
		{NULL}
};

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

int main(int argc, char** args) {
	if (!GLIB_CHECK_VERSION(2,26,0)) {
		ERROR("Need GLib 2.26.0");
	}
	PRINT("GLib %i.%i.%i present", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
	PRINT("Starting FreeJTAG w\\ Debug enabled.");
	g_type_init();
	GError* error = NULL;
	GOptionContext* context;
	context = g_option_context_new(NULL );
	g_option_context_set_summary(context, "FreeJTAG Debugging-Bridge");
	g_option_context_add_main_entries(context, options, NULL );

	if (!g_option_context_parse(context, &argc, &args, &error)) {
		ERROR("%s", error->message);
		exit(EXIT_FAILURE);
	}
	g_option_context_free(context);

	//Load configuration
	if(!fj_settings_load(NULL, &error)){
		ERROR("Can't load configuration: %s",error->message);
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

	//Add Telnet server
	PRINT("Initializing Telnet");
	GSocketService *service;
	GError* socketerror;
	PRINT("Creating socket service");
	service = g_socket_service_new();
	PRINT("Add port to socket");
	g_socket_listener_add_inet_port(G_SOCKET_LISTENER(service),3436,NULL,&socketerror);
	if(socketerror){
		ERROR("%s",socketerror->message);
	}
	PRINT("Connect callback for incoming connection");
	g_signal_connect(service,"incoming",G_CALLBACK(fj_telnet_new_connection),NULL);
	PRINT("Start socket");
	g_socket_service_start(service);

#ifdef DEBUG
	g_timeout_add_seconds(10,fj_heartbeat,NULL);
#endif
	g_main_loop_run(mainloop);

	return EXIT_FAILURE;
}
