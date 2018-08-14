#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	char buff[size];
	int fd = open("abc_10.txt",O_RDWR);

	pid_t  pid;
	pid = fork();								//First parent process executes followed by child ? 
	if (pid == 0) {
	   write(fd,"BOSANA ",7);
	   printf("This is the child process.\n");
	}
	else{
		write(fd,"SHUVAM ",7);
	    printf("This is the parent process.\n");
	}
	close(fd);

	return 0;
}


