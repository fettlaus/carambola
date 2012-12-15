/*
 * menu.c
 *
 *  Created on: Dec 13, 2012
 *      Author: bachelor
 */
#include "menu.h"
#include "telnet.h"
#include <glib.h>

static void fj_menu_answer(FJ_Client *client,const char *msg){
	GString *answer = g_string_new(msg);
	g_string_append(answer,"\n$ ");
	g_io_channel_write_chars(client->channel,answer->str,answer->len,NULL,NULL);
	g_io_channel_flush(client->channel,NULL);
	g_string_free(answer,TRUE);
}

void fj_menu_banner(FJ_Client* client){
	GInetAddress* inetaddr;
	GSocketAddress* addr = g_socket_connection_get_remote_address(client->socket,NULL);
	g_object_get(G_INET_SOCKET_ADDRESS(addr),"address",&inetaddr,NULL);
	char *banner = g_strconcat("Welcome! You are connecting from ",g_inet_address_to_string(inetaddr),NULL);
	fj_menu_answer(client,banner);
	g_free(banner);
	g_object_unref(inetaddr);
}

gboolean fj_menu_parse(FJ_Client* client, GString *input){
	GError* err = NULL;

	if(g_strcmp0(input->str,"x\r\n") == 0){
		fj_menu_answer(client,"Ist nicht drin!");
	}else if(g_strcmp0(input->str,"shutdown\r\n")==0){
		fj_menu_answer(client,"Shutting down Server!");
		fj_telnet_stop(client);
	}else if(g_strcmp0(input->str,"exit\r\n")==0||g_strcmp0(input->str,"quit\r\n")==0){
		fj_menu_answer(client,"Bye, bye!");
		return FALSE;
		//fj_telnet_disconnect_client(client);
	}else if(g_strcmp0(input->str,"disco\r\n")==0){
		fj_menu_answer(client,"Bye, other!");
		fj_telnet_disconnect_client(client);
		//fj_telnet_disconnect_client(client);
	}else{
		fj_menu_answer(client,"Keine Ahnung, was das ist.");
	}
	return TRUE;
}




