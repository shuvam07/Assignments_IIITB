// #include<stdio.h>
// #include<signal.h>
// #include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum){
	if(signum == SIGINT)
		printf("recieved SIGINT\n");
	
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO;
	action.sa_handler = handler;

	sigaction(SIGINT, &action, NULL);

	while(1)
	    sleep(1);
    return 0;
}