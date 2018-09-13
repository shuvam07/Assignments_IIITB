#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


#include<unistd.h>
int main()
{
	//mkfifo("myfifo",0666);
	char buf1[101];
	char buf2[101];
	while(1){
		fd_set rfds,wfds;
		struct timeval tv;
		int retval;

					      												

		tv.tv_sec = 10;						
		tv.tv_usec = 0;                                              
		unsigned int fd=open("myfifo",O_RDONLY);
		//unsigned int wd=dup(fd);
		FD_ZERO(&rfds); 
		FD_ZERO(&wfds);                           			 
		FD_SET(fd, &rfds);
		FD_SET(1, &wfds);
		
		retval = select(1, &rfds, &wfds, NULL, &tv);    		 


		if (retval == -1)
		   perror("select()");
		else if (retval){
			printf("Data available\n");
		   //read(fd,buf2,sizeof(buf2));
		   //printf("User1: %s",buf2);
		}
		else
		   printf("No data within 10 seconds.\n");
			

	}
  
	return 0;
}
