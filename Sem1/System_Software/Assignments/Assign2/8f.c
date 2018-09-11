// #include<stdio.h>
// #include<signal.h>
// #include<unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int nSignum){
	if(nSignum == SIGVTALRM)
		printf("Timer went off\n");
}


int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO;
	action.sa_handler = handler;

	sigaction(SIGVTALRM, &action, NULL);


	struct itimerval timer;
	timer.it_value.tv_sec = 0;
 	timer.it_value.tv_usec = 250000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 250000;
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
    while(1){
    }
}