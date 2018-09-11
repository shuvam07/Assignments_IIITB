#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	char *s = "Hello Bin";
	char s1[10];
	int fd[2] = {0,1};
	pipe(fd);
	printf("%d %d\n",fd[0],fd[1]);
	write(fd[1],s,10);
	read(fd[0],s1,10);
	printf("%s\n",s1);
}