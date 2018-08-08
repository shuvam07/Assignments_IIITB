#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 500

int main(){
	int fd,fd1;
	char buff[size];
	char filename[size];
	fd1 = open("prog.txt",0666);
	for(int i=1;i<=5;i++){
		sprintf(filename, "abc_%d.c", i);
		fd = creat(filename,0666);
		read(fd1,buff,size);
		//printf("%ld",strlen(buff));
		write(fd,buff,strlen(buff));
		
		//printf("fd=%d\n",fd);
	}
	sleep(100);
	return 0;

}


