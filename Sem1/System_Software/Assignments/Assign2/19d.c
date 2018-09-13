#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	char *file = "FIFO_FILE_MKNOD";
	mknod(file, S_IFIFO | 0666, 0);
}
