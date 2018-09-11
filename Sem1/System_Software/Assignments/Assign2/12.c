#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(){}

int main(void){
    pid_t pid, ppid;
    ppid = getpid();
    printf("ppid = %d\n", ppid);
    if((pid = fork()) == 0){ 
        sleep(2); 
        //printf("killing parent...\n");
        kill(ppid, SIGKILL);
        
        // printf("After killing parent...\n");
    }
    else{
    	printf("%d %d ",ppid, pid);
    	
        if(signal(SIGKILL,handler) == SIG_ERR)
        	printf("\ncan't catch SIGKILL\n");
        
        sleep(5); 
    }
    return 0;
}