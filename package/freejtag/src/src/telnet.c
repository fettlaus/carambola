/*
 * telnet.c
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#include "telnet.h"
#include "freejtag.h"
#include <gio/gio.h>
#include <glib.h>

gboolean fj_telnet_read_line(GIOChannel *channel, GIOCondition cond,
		gpointer data) {
	GString *s = g_string_new(NULL );
	GError *error = NULL;
	//Read Line
	GIOStatus ret = g_io_channel_read_line_string(channel, s, NULL, &error);
	if (ret == G_IO_STATUS_ERROR) {
		//free last reference
		g_object_unref(data);
		WARNING("%s", error->message);
		//return false (remove event source )
		return FALSE;
	} else {
		//TODO: Handle Data
		PRINT("Got: %s", s->str);
	}
	if (ret == G_IO_STATUS_EOF) {
		return FALSE;
	}
	return TRUE;
}

gboolean fj_telnet_new_connection(GSocketService *service,
		GSocketConnection *connection, GObject *source, gpointer data) {
	PRINT("New connection detected.");
	//keep reference to connection (don't drop it!)
	g_object_ref(connection);
	GSocket *socket = g_socket_connection_get_socket(connection);
	gint fd = g_socket_get_fd(socket);
	GIOChannel *channel = g_io_channel_unix_new(fd);

	//add channel to event. send connection as user data.
	PRINT("Connect callback for incoming data");
	g_io_add_watch(channel, G_IO_IN, (GIOFunc) fj_telnet_read_line, connection);
	return TRUE;
}
