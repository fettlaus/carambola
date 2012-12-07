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

typedef struct {
	gboolean debug;
} FJ_settings_main;

typedef struct {
	gboolean enabled;
	GString dev;
	gint baud;
	GString flags;
} FJ_settings_serial;

typedef struct{
	gboolean enabled;
	gint port;
} FJ_settings_server;

typedef struct {
	gboolean enabled;
	gint port;
} FJ_settings_telnet;

typedef struct {
	FJ_settings_main* main;
	FJ_settings_serial* serial;
	FJ_settings_server* server;
	FJ_settings_telnet* telnet;
} FJ_settings;

#define FJ_TYPE_BOOL 0
#define FJ_TYPE_INT 1
#define FJ_TYPE_STRING 2

void* fj_settings_get(int type,char* group, char* key);
void fj_settings_parse();
void fj_settings_check(GError** error);
#define FJ_SETTING_STRING(cat,key,error) g_key_file_get_string(FJ_TYPE_STRING,settings,cat,key,error)
#define FJ_SETTING_INT(cat,key,error) g_key_file_get_integer(FJ_TYPE_INT,settings,cat,key,error)
#define FJ_SETTING_BOOL(cat,key,error) g_key_file_get_boolean(FJ_TYPE_BOOL,settings,cat,key,error)

#define fj_settings_get_n(type,cat,key) { \
	g_mutex_lock(gm); \
	g_key_file_get_##type##(settings,cat,key,NULL); \
	g_mutex_release(gm); \
}while(0){}

#define fj_settings_get_bool(cat,key) *((gboolean*) fj_settings_get(FJ_TYPE_BOOL,cat,key))

gboolean fj_load_settings(GError** error);



#endif /* SETTINGS_H_ */
