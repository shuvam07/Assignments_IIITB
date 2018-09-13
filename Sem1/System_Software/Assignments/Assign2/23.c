#define _GNU_SOURCE


#include <stdio.h>
#include <ulimit.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	unsigned long n = ulimit(4);
	int fd = open("FIFO_FILE_MKF",O_RDONLY|O_NONBLOCK);
	
	printf("Max no of files a process can open %lu\n",n);
	long pipe_size = (long)fcntl(fd, F_GETPIPE_SZ);
	printf("Max size of a pipe %ld\n",pipe_size);
}