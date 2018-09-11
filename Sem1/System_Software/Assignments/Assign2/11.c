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

	action.sa_flags = 0;
	action.sa_handler = SIG_IGN;

	sigaction(SIGINT, &action, NULL);
	printf("Pressing Ctrl-C has no effect....\n");

	sleep(5);

	action.sa_handler = SIG_DFL;

	sigaction(SIGINT, &action, NULL);
	printf("Default resetted.. Pressing Ctrl-C has effect now....\n");
	
	sleep(5);
    return 0;
}