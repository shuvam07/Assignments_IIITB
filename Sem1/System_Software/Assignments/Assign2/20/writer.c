#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main()
{
	mkfifo("myfifo",0666);
	char buf1[101];
	char buf2[101];
	while(1){
		int fd = open("myfifo",O_WRONLY);
		fgets(buf1,sizeof(buf1),stdin);
		write(fd,buf1,strlen(buf1)+1);
		close(fd);

	}

	return 0;
}
