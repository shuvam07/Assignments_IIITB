#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	char buff[size];
	int fd = open("abc_3.c",O_RDONLY);
	int fd1 = creat("abc_7.txt",0777);
	int sz = read(fd,buff,size);
	printf("%d",sz);
	write(fd1,buff,sz);
	return 0;
}


