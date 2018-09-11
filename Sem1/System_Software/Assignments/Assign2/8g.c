#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <sys/time.h>


void handler(int nSignum, siginfo_t* si, void* vcontext){
	//if(nSignum == SIGPROF)
		printf("Signal Profiling Encountered\n");
	exit(1);
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = handler;

	sigaction(SIGPROF, &action, NULL);

	struct itimerval timeout={0};
  	timeout.it_value.tv_sec=1;
    setitimer (ITIMER_PROF, &timeout, NULL);
    while(1){};
}