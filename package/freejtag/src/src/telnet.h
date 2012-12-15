/*
 * telnet.h
 *
 *  Created on: Oct 22, 2012
 *      Author: bachelor
 */

#ifndef TELNET_H_
#define TELNET_H_
#include<gio/gio.h>

typedef struct{
	GSocketConnection* socket;
	GIOChannel* channel;
	GSocketService* service;
	GSource* source;
} FJ_Client;

void fj_telnet_disconnect_client(FJ_Client *client);

void fj_telnet_change_port(GSocketService* service, gint port, GError** error);

void fj_telnet_run(GMainLoop* parent);

void fj_telnet_stop(FJ_Client *client);



#endif /* TELNET_H_ */
