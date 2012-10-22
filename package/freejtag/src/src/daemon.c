/*
 * daemon.c
 *
 *  Created on: Oct 12, 2012
 *      Author: bachelor
 */
#include "freejtag.h"

extern gboolean nodetach;

void daemon_fork(){

	//become autonomous
	pid_t pid, sid;
	if(!nodetach){
		PRINT("We have to detach...\n");
		PRINT("Forking\n");
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
	PRINT("SetSID\n");
	sid = setsid();
	if(sid < 0){
		syslog(LOG_EMERG,"%s","Couldn't get SID");
		exit(EXIT_FAILURE);
	}

	//TODO: ignore signals

	//become autonomous a second time
	if(!nodetach){
		PRINT("Second fork...\n");
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
void daemon_init(mode_t mask){
	// Change working directory
	PRINT("Changing directory\n");
	if(chdir("/")<0){
		syslog(LOG_EMERG,"%s","Couldn't change to root");
		exit(EXIT_FAILURE);
	}

	//set file permissions
	PRINT("Setting umask\n");
	umask(mask);

	//open syslog
	PRINT("Opening log\n");
	openlog("freejtag",LOG_CONS,LOG_DAEMON);
}
