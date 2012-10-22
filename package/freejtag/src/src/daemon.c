/*
 * daemon.c
 *
 *  Created on: Oct 12, 2012
 *      Author: bachelor
 */

#include "daemon.h"
#include "freejtag.h"
#include <glib.h>
#include <stdlib.h>
#include <syslog.h>

extern gboolean nodetach;

void fj_daemon_fork(){

	//become autonomous
	pid_t pid, sid;
	if(!nodetach){
		PRINT("We have to detach...");
		PRINT("Forking");
		pid = fork();
		if(pid <0){
			syslog(LOG_EMERG,"%s","Couldn't fork child process");
			exit(EXIT_FAILURE);
		}
		if(pid>0){
			exit(EXIT_SUCCESS);
		}
	}

	//get SID
	PRINT("SetSID");
	sid = setsid();
	if(sid < 0){
		syslog(LOG_EMERG,"%s","Couldn't get SID");
		exit(EXIT_FAILURE);
	}

	//TODO: ignore signals

	//become autonomous a second time
	if(!nodetach){
		PRINT("Second fork...");
		pid = fork();
		if(pid <0){
			syslog(LOG_EMERG,"%s","Couldn't fork second child process");
			exit(EXIT_FAILURE);
		}
		if(pid>0){
			exit(EXIT_SUCCESS);
		}
	}


}
void fj_daemon_init(mode_t mask){
	// Change working directory
	PRINT("Changing directory");
	if(chdir("/")<0){
		syslog(LOG_EMERG,"%s","Couldn't change to root");
		exit(EXIT_FAILURE);
	}

	//set file permissions
	PRINT("Setting umask");
	umask(mask);

	//open syslog
	PRINT("Opening log");
	openlog("freejtag",LOG_CONS,LOG_DAEMON);
}
