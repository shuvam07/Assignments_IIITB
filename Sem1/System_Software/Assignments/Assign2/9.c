#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>

int flag = 0;

// void handler(int signum){
// 	signal(SIGINT,SIG_IGN);
// 	if(signum == SIGINT){
// 		printf("IGNORING SIGNAL SIGINT\n");
// 	}
// 	raise(SIGINT);
// 	flag = 1;
// }

int main() {

	signal(SIGINT, SIG_IGN);
	printf("Pressing Ctrl-C has no effect....\n");
	sleep(10);
	printf("Default resetted.. Pressing Ctrl-C has effect now....\n");
	signal(SIGINT, SIG_DFL);
	sleep(10);
    return 0;
}