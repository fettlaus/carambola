/*
 * settings.c
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */
#include "freejtag.h"
#include "settings.h"
#include <glib.h>

GKeyFile* settings;

gboolean fj_load_settings(GError** error){
	settings = g_key_file_new();
#ifdef DEBUG
	gchar *conffile = "conf/freejtag.cfg";
#else
	gchar *conffile = g_strconcat(SYSCONFDIR,"/",PACKAGE,".cfg",NULL);
#endif
	PRINT("Loading config from %s",conffile);
	g_key_file_load_from_file(settings,conffile,G_KEY_FILE_NONE,error);
	if(*error!=NULL){
		return FALSE;
	}
	return TRUE;
}
