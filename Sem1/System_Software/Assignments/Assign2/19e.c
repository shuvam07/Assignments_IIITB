#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
       
int main(){

	char *file = "FIFO_FILE_MKF";
	mkfifo(file, 0666);

}
