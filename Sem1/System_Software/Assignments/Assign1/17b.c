#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(){
	char buff[20];
	int fd=open("ticket.txt",O_RDWR);
	struct flock lock;
	lock.l_type=F_WRLCK;
	fcntl(fd,F_SETLKW,&lock);
	read(fd,buff,20);
	int ticket = atoi (buff);
	ticket++;
	printf("Ticket number %d\n",ticket);
	lseek (fd,0,0);
	sprintf(buff, "%d", ticket);
	write(fd,buff,strlen(buff));
	printf("Press enter to unlock");
	getchar();
	lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
    close(fd);
	return 0;
}



