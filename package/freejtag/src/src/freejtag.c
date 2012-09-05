/*
 ============================================================================
 Name        : freejtag.c
 Author      : Arne Wischer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>

int main(void) {
	//become autonomous
	pid_t pid, sid;
	pid = fork();
	if(pid <0){
		syslog(LOG_EMERG,"%s","Couldn't fork child process");
		exit(EXIT_FAILURE);
	}
	if(pid>0){
		exit(EXIT_SUCCESS);
	}

	//set file permissions
	umask(0);

	//open syslog
	openlog("freejtag",LOG_CONS,LOG_DAEMON);

	//get SID
	sid = setsid();
	if(sid < 0){
		syslog(LOG_EMERG,"%s","Couldn't get SID");
		exit(EXIT_FAILURE);
	}

	// Change working directory
	if(chdir("/")<0){
		syslog(LOG_EMERG,"%s","Couldn't change to root");
		exit(EXIT_FAILURE);
	}

	//FreeJTAG Init
	time_t t;
	struct tm* zeit;

	syslog(LOG_INFO,"%s","FreeJTAG startet successfully");
	while(1){
		time(&t);
		zeit = localtime(&t);
		printf("Heartbeat at %02i:%02i:%02i\n",zeit->tm_hour,zeit->tm_min,zeit->tm_sec);
		sleep(10);
	}
	return EXIT_FAILURE;
}
