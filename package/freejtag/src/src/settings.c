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

gchar* fj_setting_get_filename(){
#ifdef DEBUG
	return "conf/freejtag.cfg";
#else
	return g_strconcat(SYSCONFDIR,"/",PACKAGE,".cfg",NULL);
#endif
}

gboolean fj_settings_load(GError** error){
	gchar* file;
	file = fj_setting_get_filename();
	fj_settings_file = g_key_file_new();
	PRINT("Loading config from %s",file);
	g_key_file_load_from_file(fj_settings_file,file,G_KEY_FILE_NONE,error);
	if(*error!=NULL){
		return FALSE;
	}
	fj_settings_check(error);
	if(*error!=NULL){
		return FALSE;
	}
	PRINT("Config Sanity Check passed");
	return TRUE;
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

void fj_settings_save(GError** error){
	gchar* cont;
	gsize length;
	cont = g_key_file_to_data(fj_settings_file,&length,NULL);
	g_file_set_contents(fj_setting_get_filename(),cont,length,error);
}
