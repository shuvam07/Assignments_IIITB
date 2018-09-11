#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	char *s = "Hello World";
	char s1[10];
	int fd[2];
	if(pipe(fd) == -1)
		return -1;
	int pid = fork();
	if(pid == 0){
		close(fd[1]);
		read(fd[0],s1,11);
		printf("%s\n",s1);
	}
	else if(pid>0){
		close(fd[0]);
		write(fd[1],"Yup....Done",11);
	}
	else
		return 1;
}