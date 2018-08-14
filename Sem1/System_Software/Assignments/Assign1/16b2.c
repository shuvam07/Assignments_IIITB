#include <unistd.h>
#include <stdio.h>
#include<fcntl.h>


int main(){
	int fd=open("abc.txt",O_RDWR);
	write(fd,"LOCKED",6);
	printf("Press enter to unlock");
	getchar();
	// lock.l_type = F_UNLCK;
 //    fcntl (fd, F_SETLK, &lock);
	return 0;
}



