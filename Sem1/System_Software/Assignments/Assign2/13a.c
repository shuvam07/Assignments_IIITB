#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(int signum){
    if(signum == SIGSTOP){
        printf("CAUGHT SIGSTOP\n");
    }
}

int main(void){	
    printf("pid = %d\n",getpid());
    if(signal(SIGSTOP,handler) == SIG_ERR)
    	printf("\nCAN'T CATCH SIGSTOP\n");
        
    sleep(500); 
    return 0;
}