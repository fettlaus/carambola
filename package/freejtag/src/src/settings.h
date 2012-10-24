/*
 * settings.h
 *
 *  Created on: Oct 24, 2012
 *      Author: bachelor
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <glib.h>

extern GKeyFile* settings;

#define FJ_SETTING_STRING(cat,key,error) g_key_file_get_string(settings,cat,key,error)
#define FJ_SETTING_INT(cat,key,error) g_key_file_get_integer(settings,cat,key,error)
#define FJ_SETTING_BOOL(cat,key,error) g_key_file_get_boolean(settings,cat,key,error)


gboolean fj_load_settings(GError** error);



#endif /* SETTINGS_H_ */
