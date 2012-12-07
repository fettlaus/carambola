/*
 * settings.c
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */
#include "freejtag.h"
#include "settings.h"
#include <glib.h>

GKeyFile* fj_settings_file;
FJ_settings* settings;
GMutex* gm;

void fj_settings_conf_init();
void fj_settings_conf_free();

gboolean fj_load_settings(GError** error){
	fj_settings_file = g_key_file_new();
	gm = g_mutex_new();
#ifdef DEBUG
	gchar *conffile = "conf/freejtag.cfg";
#else
	gchar *conffile = g_strconcat(SYSCONFDIR,"/",PACKAGE,".cfg",NULL);
#endif
	PRINT("Loading config from %s",conffile);
	g_key_file_load_from_file(fj_settings_file,conffile,G_KEY_FILE_NONE,error);
	if(*error!=NULL){
		return FALSE;
	}
	fj_settings_check(error);
	if(*error!=NULL){
		return FALSE;
	}
	PRINT("Config Sanity Check passed");
	fj_settings_conf_init(settings);
	return TRUE;
}

void fj_settings_conf_init(){
	settings = g_new(FJ_settings, 1);
	settings->main = g_new(FJ_settings_main, 1);
	settings->serial = g_new(FJ_settings_serial, 1);
	settings->server = g_new(FJ_settings_server, 1);
	settings->telnet = g_new(FJ_settings_telnet, 1);
}

void fj_settings_conf_free(){
	g_free(settings->main);
	g_free(settings->serial);
	g_free(settings->server);
	g_free(settings->telnet);
	g_free(settings);
}

void fj_settings_check(GError** error){
	if(!g_key_file_get_boolean(fj_settings_file,"main","daemonize",error)) return;
	if(!g_key_file_get_boolean(fj_settings_file,"serial","enabled",error)) return;
	if(!g_key_file_get_string(fj_settings_file,"serial","dev",error)) return;
	if(!g_key_file_get_integer(fj_settings_file,"serial","baud",error)) return;
	if(!g_key_file_get_string(fj_settings_file,"serial","flags",error)) return;
	if(!g_key_file_get_boolean(fj_settings_file,"server","enabled",error)) return;
	if(!g_key_file_get_integer(fj_settings_file,"server","port",error)) return;
	if(!g_key_file_get_boolean(fj_settings_file,"telnet","enabled",error)) return;
}

void* fj_settings_get(int type, char* group, char* key){
	if(group == "main"){
		if(key == "debug") return &settings->main->debug;
	}else if(group == "serial"){
		if (key == "enabled") return &settings->serial->enabled;
	}
	return NULL;
}
