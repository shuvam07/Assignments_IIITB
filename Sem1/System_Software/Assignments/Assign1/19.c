#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <time.h>

#define size 100

int main(){
	
	clock_t start, end;
     	double cpu_time_used;
     	start = clock();
        int pid = getpid();
	//sleep(1);
     	end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("pid = %d\nTime Elapsed(in sec) = %f\n",pid,cpu_time_used);
	return 0;
}



