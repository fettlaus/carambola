/*
 * menu.h
 *
 *  Created on: Dec 13, 2012
 *      Author: bachelor
 */

#ifndef MENU_H_
#define MENU_H_

#include "telnet.h"
#include <glib.h>

void fj_menu_banner(FJ_Client* client);
gboolean fj_menu_parse(FJ_Client *client, GString *input);




#endif /* MENU_H_ */
