/*
 * test_settings.c
 *
 *  Created on: Dec 12, 2012
 *      Author: bachelor
 */
#include <glib.h>
#include "test_settings.h"
#include "../src/settings.h"

void test_settings_init(void){
	fj_setting_get_filename();
	g_assert(1==1);
}

void test_settings_toggle(void){
	GError *err;
	g_key_file_set_boolean(fj_settings_file,"main","daemonize",FALSE);
	g_assert(!g_key_file_get_boolean(fj_settings_file,"main","daemonize",&err));
	g_assert_no_error(err);
	g_key_file_set_boolean(fj_settings_file,"main","daemonize",TRUE);
	g_assert(g_key_file_get_boolean(fj_settings_file,"main","daemonize",&err));
	g_assert_no_error(err);
}
