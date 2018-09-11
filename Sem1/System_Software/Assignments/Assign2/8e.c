#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum){
	if(signum == SIGALRM)
		printf("Timer went off\n");
	exit(1);
	
}


int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = 0;
	action.sa_handler = handler;

	sigaction(SIGALRM, &action, NULL);


	struct itimerval timer;
	timer.it_value.tv_sec = 0;
 	timer.it_value.tv_usec = 250000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;
    setitimer (ITIMER_REAL, &timer, NULL);
    while(1){
    }
}



						