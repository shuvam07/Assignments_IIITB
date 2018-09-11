#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>


void handler(int nSignum, siginfo_t* si, void* vcontext){
	printf("Segmentation fault Encountered\n");
	exit(1);
}

int main() {

    struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;

	sigaction(SIGSEGV, &action, NULL);


	int* x = 0;
  	int y = *x;
}