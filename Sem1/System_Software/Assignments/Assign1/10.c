#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	char buff[size]={"ABCDEFGHIJ"};
	char c;
	int fd = open("abc_10.txt",O_RDWR);
	write(fd,buff,strlen(buff));
	int ret = lseek (fd,10,SEEK_CUR);
	write(fd,buff,strlen(buff));
	close(fd);
	printf("%d\n",ret);
	int fd1 = open("abc_10.txt",O_RDONLY);
	read(fd1,buff,size);
	int i=0;
	while((c=buff[i++])!='Z'){
		printf("%c",c);
	}
	return 0;
}


