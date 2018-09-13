#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


#include<unistd.h>
int main()
{
	//printf("ok");
	mkfifo("myfifo",0666);
	char buf1[101];
	char buf2[101];
	//printf("ok1");
	while(1){
		
		//printf("ok2");			

		int fd1 = open("myfifo",O_RDONLY);
		read(fd1,buf2,sizeof(buf2));
		printf("User1: %s",buf2);
		close(fd1);

	}

	return 0;
}
