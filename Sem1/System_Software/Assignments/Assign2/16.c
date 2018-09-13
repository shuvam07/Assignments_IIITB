
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	int pfd1[2],pfd2[2];
	char buffer[70],reader[70];
	pipe(pfd1);
	pipe(pfd2);
	if(fork()){
		close(pfd1[0]);
		close(pfd2[1]);
		printf("This is parent. Message to child : ");
		scanf(" %[^\n]s",buffer);
		write(pfd1[1],buffer,70);	
		printf("This is parent. Message from child : ");	
		read(pfd2[0],reader,70);	
		printf(" %s\n",reader);		
	}
	else{
		close(pfd2[0]);
		close(pfd1[1]);
		printf("This is child. Message from parent : ");	
		read(pfd1[0],reader,70);	
		printf("%s\n",reader);		
		printf("This is child. Message to parent : ");
		scanf(" %[^\n]s",buffer);
		write(pfd2[1],buffer,70);	
	}
	wait(0);
	return 0;
}