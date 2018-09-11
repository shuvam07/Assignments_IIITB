#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <time.h>

int main()
{
  clock_t t1 = clock();
  for(int i=0;i<100;i++){
  	getppid();
  }
  double tt = ((double)(clock() - t1)) / CLOCKS_PER_SEC;
  printf("Time in sec %f\n",tt);
}