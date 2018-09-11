#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>


sigjmp_buf point;

void handler(int nSignum, siginfo_t* si, void* vcontext){
    if(nSignum == SIGFPE)
        printf("SIGFPE Encountered\n");
    //longjmp(point, 1);
    exit(1);
}

int main() {

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;

    sigaction(SIGFPE, &action, NULL);


    int i = 0;
    int j = 2/i;
}