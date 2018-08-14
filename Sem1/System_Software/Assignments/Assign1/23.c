#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	

	if(!fork()){
		printf("Child Process execution completed %d\n",getpid());
	}
	else{
		printf("waiting for input in parent process\n");
		getchar();
	}

	return 0;
}

