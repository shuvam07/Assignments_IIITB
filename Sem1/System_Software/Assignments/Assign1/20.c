#include<stdio.h>
#include<sys/resource.h>
#include <time.h>

int main(){
	int prio = getpriority(PRIO_PROCESS,0);
	printf("Priority of current process = %d\n",prio);
	return 0;
}



