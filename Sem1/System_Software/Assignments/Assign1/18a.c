// ./18a 4 3 (from 4th byte write 3 bytes )



#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int lock_reg(int fd, int cmd, int type, long int offset, int whence, long int len)
{
    struct flock lock;

    lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
    lock.l_start = offset;  /* byte offset, relative to l_whence */
    lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
    lock.l_len = len;       /* #bytes (0 means to EOF) */

    return(fcntl(fd, cmd, &lock));
}

int main(int argc, char *argv[]){
	int fd=open("abc_10.txt",O_RDWR);
	char buffer[50]={'\0'};
	lseek(fd,atoi(argv[1]),SEEK_CUR);
	lock_reg(fd,F_SETLKW,F_WRLCK,atoi(argv[1]),SEEK_CUR,atoi(argv[2]));
	//read(fd,buffer,3);
	printf("locked record abc_10.txt\n");
	write(fd,"abc\n",atoi(argv[2]));
	printf("Press enter to unlock\n");
	getchar();
	lock_reg(fd,F_SETLKW,F_UNLCK,atoi(argv[1]),SEEK_CUR,atoi(argv[2]));
	close(fd);
	return 0;
}

