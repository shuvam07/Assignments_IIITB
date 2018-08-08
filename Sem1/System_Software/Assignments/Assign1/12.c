#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define size 100

int main(){
	
	/*http://www.informit.com/articles/article.aspx?p=99706&seqNum=13*/
	
	char buff[size];
	char c;
	int fd = open("abc_10.txt",O_RDWR);
	int mode = fcntl(fd,F_GETFL);
	int accmode = mode & O_ACCMODE;
	if(accmode == O_RDONLY) printf("read only\n");
	if(accmode == O_WRONLY) printf("write only\n");
	if(accmode == O_RDWR) printf("read write\n");
	//printf("%d",mode);
	return 0;
}


