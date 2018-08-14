#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 50

int main(){
	int fd;
	char buff[size];

	fd = creat("abc.txt",0744);

	printf("fd=%d\n",fd);
	return 0;

}


