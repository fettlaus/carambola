/*
 * menu.h
 *
 *  Created on: Dec 13, 2012
 *      Author: bachelor
 */

#ifndef MENU_H_
#define MENU_H_

#include <boost/array.hpp>
#include <boost/mpl/bool.hpp>
#include <stdlib.h>

class menu{
public:

private:
	void fj_menu_banner(FJ_Client* client);
	bool fj_menu_parse(FJ_Client client, std::string input);
};







#endif /* MENU_H_ */
