#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char* argv[], char *env[])
{
	int i=0;
	char *filename="abc_10.txt";
	struct flock lock;
	printf("opening file abc.txt\n");
	int fd=open("abc_10.txt",O_RDWR);
	printf("locking file abc.txt for write operation\n");
	lock.l_type= F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	printf("locked file abc.txt\n");
	write(fd,"LOCKED_1",8);
	printf("Press enter to unlock\n");
	getchar();
	close (fd);
	lock.l_type = F_UNLCK;
 	fcntl (fd, F_SETLKW, &lock);
 	
 	return 0;
}
