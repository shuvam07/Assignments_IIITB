#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	char buff[size];
	int fd = creat("ticket.txt",0777);
	write(fd,"20",2);
	close(fd);
	return 0;
}


