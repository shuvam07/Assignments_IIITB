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
	if(signum == SIGALRM)
		printf("recieved SIGALRM\n");
	
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = 0;
	action.sa_handler = handler;

	sigaction(SIGALRM, &action, NULL);


	alarm(1);
	while(1){
		pause();
	}
}