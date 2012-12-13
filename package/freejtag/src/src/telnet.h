/*
 * telnet.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef TELNET_H_
#define TELNET_H_
#include<gio/gio.h>

gboolean fj_telnet_read_line(GIOChannel *channel, GIOCondition cond,
		gpointer data);
/**
 * aeaea
 */
gboolean fj_telnet_new_connection(GSocketService *service,
		GSocketConnection *connection, GObject *source, gpointer data);

#endif /* TELNET_H_ */
