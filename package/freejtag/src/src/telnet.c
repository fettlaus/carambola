/*
 * telnet.c
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "telnet.h"
#include "freejtag.h"
#include "menu.h"
#include <gio/gio.h>
#include <glib.h>

// new mainloop
// new socketlistener
// attach_callback()
// on new connection:
// 		callback attaches watch and callback
// on server restart command:
// 		change port in cfg
//		close_connections()
//		attach_callback()
// on shutdown:
//		close_connections()
//		stop socketlistener
//		free resources
//
//
static GMainLoop *telnetloop;
static GSList* clientlist;

static void fj_telnet_close_connections(){
	//TODO: Write close_connections()
	//		warn all clients
	//		disconnect all clients (remove callback from watch)
	//		remove callback for new connections
	//		remove inetport
}

void fj_telnet_disconnect_client(FJ_Client *client){
	g_io_channel_shutdown(client->channel,TRUE,NULL);
	g_object_unref(client->socket);
}

static gboolean fj_telnet_read_line(GIOChannel *channel, GIOCondition cond,
		gpointer data) {
	GString *s = g_string_new(NULL );
	GError *error = NULL;
	//Read Line
	GIOStatus ret = g_io_channel_read_line_string(channel, s, NULL, &error);
	if (ret == G_IO_STATUS_ERROR || ret == G_IO_STATUS_EOF) {
		// close io Channel and free last reference
		g_io_channel_shutdown(((FJ_Client*)data)->channel,TRUE,&error);
		g_object_unref(((FJ_Client*)data)->socket);
		WARNING("%s", error->message);
		//return false (remove event source )
		return FALSE;
	}
	fj_menu_parse((FJ_Client*)data, s);
	PRINT("Got: %s", s->str);
	return TRUE;
}

static gboolean fj_telnet_new_connection(GSocketService *service,
		GSocketConnection *connection, GObject *source, gpointer data) {
	PRINT("New connection detected.");
	///We need to keep a reference to the connection. (don't drop it!)
	g_object_ref(connection);
	GSocket *socket = g_socket_connection_get_socket(connection);
	gint fd = g_socket_get_fd(socket);
	GIOChannel *channel = g_io_channel_unix_new(fd);

	// add client to list
	FJ_Client* client = g_new(FJ_Client,1);
	client->channel = channel;
	client->socket = connection;
	client->service = service;
	clientlist = g_slist_prepend(clientlist,client);

	//add channel to event. send connection as user data.
	PRINT("Connect callback for incoming data");
	g_io_add_watch(channel, G_IO_IN, (GIOFunc) fj_telnet_read_line, client);

	fj_menu_banner(client);
	return TRUE;
}

/**
 * Attach port as specified in config-file to service. Then connect signal \"incoming\" from the service to callback fj_telnet_new_connection().
 * @see fj_telnet_new_connection
 * @param service
 * @param error error at opening port
 */
static void fj_telnet_attach_callback(GSocketService *service, GError **werror){
	PRINT("Add port to socket");
	GError *err = NULL;
	//TODO: read port from cfg
	g_socket_listener_add_inet_port(G_SOCKET_LISTENER(service),3436,NULL,&err);
	if(err != NULL){
		ERROR("%s",err->message);
	}
	PRINT("Connect callback for incoming connection");
	g_signal_connect(service,"incoming",G_CALLBACK(fj_telnet_new_connection),NULL);
	PRINT("Start socket");
	g_socket_service_start(service);
}

/**
 * Start the Telnet process with a new GMainLoop. Needs to run in a separate thread.
 */
void fj_telnet_run(GMainLoop* parent){
	gboolean run;
	// new mainloop
	GMainContext* context;
	context = g_main_context_new();
	telnetloop = g_main_loop_new(context,FALSE);

	GSocketService *service;
	GError* socketerror;
	PRINT("Creating socket service");
	service = g_socket_service_new();
	fj_telnet_attach_callback(service,&socketerror);
	// TODO: attach restart signal?

	g_main_loop_run(telnetloop);

	// now we have to shutdown
	g_socket_service_stop(service);
	fj_telnet_close_connections();

	// TODO: free mainloop
	// TODO: exit parent mainloop
	return;
}

void fj_telnet_stop(FJ_Client *client){
	g_main_loop_quit(telnetloop);
}

void fj_telnet_change_port(GSocketService* service, gint port, GError** error){
	//TODO: change port in cfg
	fj_telnet_close_connections();
	fj_telnet_attach_callback(service,error);
}
