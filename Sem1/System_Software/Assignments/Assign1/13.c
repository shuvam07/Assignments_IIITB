#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(void)
{
   fd_set rfds;
   struct timeval tv;
   int retval;

   	/* Watch stdin (fd 0) to see when it has input. */
   FD_ZERO(&rfds);                           			 // pointing to a garbage
   FD_SET(0, &rfds);			      			// pointing to STDIN 									

   tv.tv_sec = 5;						// time it has to wait for data(5sec here)
   tv.tv_usec = 0;                                              // time in microsecond
   unsigned int fd=open("abc.txt",0777);
   unsigned int wd=dup(fd);
   printf("%u %u",rfds,wd);
   retval = select((rfds>wd?rfds:wd)+1, &rfds, &wd, NULL, &tv);    		 // will wait if no data is in read,write or exe file descriptor 


   if (retval == -1)
       perror("select()");
   else if (retval)
       printf("Data is available now.\n");
   else
       printf("No data within five seconds.\n");

   exit(EXIT_SUCCESS);
}
