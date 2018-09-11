#include <stdio.h>
#include <stdint.h>
#include <sys/resource.h>
#include <string.h>

int main()
{
  struct rlimit rlim;
  rlim.rlim_cur = 32768;
  rlim.rlim_max = 32768;
  setrlimit(RLIMIT_MEMLOCK,&rlim);

  memset(&rlim,0,sizeof(rlim));
  getrlimit(RLIMIT_MEMLOCK,&rlim);
  printf("RLIMIT_MEMLOCK\t%lu\t%lu\n",rlim.rlim_cur,rlim.rlim_max);
}