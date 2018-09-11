#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	char *file = "FIFO_FILE";
	mknod(file, S_IFIFO | 0666, 0);
}
