/*
 * settings.h
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <glib.h>

extern GKeyFile* fj_settings_file;

#define FJ_TYPE_BOOL 0
#define FJ_TYPE_INT 1
#define FJ_TYPE_STRING 2

gchar* fj_setting_get_filename();
void* fj_settings_get(int type,char* group, char* key);
void fj_settings_check(GError** error);
void fj_settings_save(GError** error);

#define fj_settings_get_n(type,cat,key) { \
	g_mutex_lock(gm); \
	g_key_file_get_##type##(settings,cat,key,NULL); \
	g_mutex_release(gm); \
}while(0){}

#define fj_settings_get_bool(cat,key) *((gboolean*) fj_settings_get(FJ_TYPE_BOOL,cat,key))

gboolean fj_settings_load(GKeyFile* keyfile, GError** error);



#endif /* SETTINGS_H_ */
