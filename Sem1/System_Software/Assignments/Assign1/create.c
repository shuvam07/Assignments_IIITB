#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 50

int main(){
	int fd;
	char buff[size];

	fd = open("abc.txt", O_RDWR, 0777);

//	fd = open("abc.txt",777);
	
	scanf("%[^\n]",buff);

	write(fd,buff,strlen(buff));

	printf("%s",buff);

	if(!close(fd)){
		printf("\nSuccess\n");
	}
	return 0;

}


