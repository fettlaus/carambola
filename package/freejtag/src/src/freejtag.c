/*
 ============================================================================
 Name        : freejtag.c
 Author      : Arne Wischer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
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

int main(int argc, char** args) {
	GError* error = NULL;
	GOptionContext* context;
	context = g_option_context_new(NULL);
	g_option_context_set_summary(context,"FreeJTAG Debugging-Bridge");
	g_option_context_add_main_entries(context,options,NULL);

	if(!g_option_context_parse(context,&argc,&args,&error)){
		printf("Error: %s\n",error->message);
		exit(EXIT_FAILURE);
	}
	g_option_context_free(context);
	PRINT("Started FreeJTAG. Debug enabled.\n");
	PRINT("GLib %i.%i.%i present\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
	if(!nodetach){
		daemon_fork();
	}

	daemon_init(0);

	//FreeJTAG Init
	syslog(LOG_INFO,"%s","FreeJTAG startet successfully");

	time_t t;
	struct tm* zeit;
	while(1){
#ifdef DEBUG
			time(&t);
			zeit = localtime(&t);
			printf("Heartbeat at %02i:%02i:%02i\n",zeit->tm_hour,zeit->tm_min,zeit->tm_sec);
#endif
		sleep(10);
	}
	return EXIT_FAILURE;
}
