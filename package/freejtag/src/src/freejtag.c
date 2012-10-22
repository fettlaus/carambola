/*
 ============================================================================
 Name        : freejtag.c
 Author      : Arne Wischer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <glib.h>
#include "daemon.h"
#include "freejtag.h"

gboolean nodetach = FALSE;

static GOptionEntry options[] = {
		{"nodetach",0,0,G_OPTION_ARG_NONE,&nodetach,"disable detaching from parent process",NULL},
		{NULL}
};

#ifdef DEBUG
gboolean heartbeat(){
	time_t t;
	struct tm* zeit;
	time(&t);
	zeit = localtime(&t);
	PRINT("Heartbeat at %02i:%02i:%02i",zeit->tm_hour,zeit->tm_min,zeit->tm_sec);
	return TRUE;
}
#endif

int main(int argc, char** args) {
	if(!GLIB_CHECK_VERSION(2,26,0)){
		ERROR("Need GLib 2.26.0");
	}
	PRINT("GLib %i.%i.%i present", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
	PRINT("Starting FreeJTAG w\\ Debug enabled.");
	GError* error = NULL;
	GOptionContext* context;
	context = g_option_context_new(NULL);
	g_option_context_set_summary(context,"FreeJTAG Debugging-Bridge");
	g_option_context_add_main_entries(context,options,NULL);

	if(!g_option_context_parse(context,&argc,&args,&error)){
		ERROR("%s",error->message);
		exit(EXIT_FAILURE);
	}
	g_option_context_free(context);
	if(!nodetach){
		daemon_fork();
	}

	daemon_init(0);

	//FreeJTAG Init
	syslog(LOG_INFO,"%s","FreeJTAG startet successfully");

	//Main Loop
	GMainLoop* mainloop;
	mainloop = g_main_loop_new(NULL,FALSE);
#ifdef DEBUG
	g_timeout_add_seconds(10,heartbeat,NULL);
#endif
	g_main_loop_run(mainloop);

	return EXIT_FAILURE;
}
