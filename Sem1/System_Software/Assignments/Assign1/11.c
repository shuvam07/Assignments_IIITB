#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	char buff[size];
	char c;
	int fd = open("abc_10.txt",O_RDWR);
	int fd1 = dup2(fd,20);                      // using dup2 you can specify a specific file descriptor value (here 20)
	int rd = read(fd,buff,size);
	printf("%u ",fd1);
	write(fd1,"SHUVAM ",7);    
	write(fd,"BOSANA",6);

	int fd2 = fcntl(fd,1,20);                   // should have used file descriptor greater than 20 which is available
	printf("%u",fd2);
	close(fd);
	return 0;
}


