/*
 * daemon.h
 *
 *  Created on: Oct 12, 2012
 *      Author: bachelor
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include <sys/types.h>
/*
 * Basically:
 * fork()
 * setsid()
 * ignore signals
 * fork()
 * Source: http://openbook.galileocomputing.de/linux_unix_programmierung/Kap07-011.htm
 */
void fj_daemon_fork();

/*
 * chdir()
 * umask()
 * openlog()
 * Source: http://openbook.galileocomputing.de/linux_unix_programmierung/Kap07-011.htm
 */
void fj_daemon_init(mode_t mask);

#endif /* DAEMON_H_ */
