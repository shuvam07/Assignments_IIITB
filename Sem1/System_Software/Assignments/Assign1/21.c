#include<stdio.h>
#include<sys/resource.h>
#include <unistd.h>

int main(){
	
	 pid_t  pid;
	 pid = fork();
	 if (pid == 0) 
	    printf("This is the child process. My pid is %d and my parent's id is %d.\n", getpid(), getppid());
	 else 
	     printf("This is the parent process. My pid is %d and my parent's id is %d.\n", getpid(), getppid());
	
}



