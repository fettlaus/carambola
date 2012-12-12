/*
 * test_test.c
 *
 *  Created on: Dec 12, 2012
 *      Author: bachelor
 */
#include <glib.h>
#include "test_settings.h"

int main(int argc,char *argv[]){
	g_test_init(&argc,&argv,NULL);
	g_test_add_func("/testsettings/Init",test_settings_init);
	return g_test_run();
}
