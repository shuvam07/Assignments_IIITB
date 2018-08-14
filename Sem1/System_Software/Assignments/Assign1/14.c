#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat s;	
	stat(argv[1],&s);
	unsigned int m =s.st_mode;
	if(S_ISREG(m))
		printf("Regular File\n"); 
	else if(S_ISDIR(m))
		printf("Directory\n"); 
	else if(S_ISCHR(m))
		printf("character device\n"); 		// /dev/full
	else if(S_ISBLK(m))
		printf("block device\n"); 		// /dev/sda
	else if(S_ISFIFO(m))
		printf("FIFO (named pipe)\n"); 		// /run/systemd/initctl/fifo
	else if(S_ISLNK(m))
		printf("symbolic link\n"); 		// 
	else if(S_ISSOCK(m))
		printf("Socket\n"); 			// /var/run/acpid.socket
	else
		printf("Invalid File");			

}
