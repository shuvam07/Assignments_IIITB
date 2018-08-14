#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<sched.h>


/* https://stackoverflow.com/questions/10704983/operation-not-permitted-while-setting-new-priority-for-thread */

void printSchedulingPolicy()
{
  	int which;
	which = sched_getscheduler(0);
	switch (which) {
	case SCHED_OTHER: 
			printf("default scheduling is being used\n");		
		  	break;
	case SCHED_FIFO:
			printf("fifo scheduling is being used\n");		
		  	break;
	case SCHED_RR:		
			printf("round robin scheduling is being used\n");		
		  	break;
	}		
}

 
int main()
{
	printSchedulingPolicy();
	struct sched_param p;
	p.sched_priority = 0;   
	if (sched_setscheduler(0, SCHED_FIFO, &p) != 0) {
		printf("Failed to set the scheduler\n");
	}	   	
	printSchedulingPolicy();
    return 0;
}