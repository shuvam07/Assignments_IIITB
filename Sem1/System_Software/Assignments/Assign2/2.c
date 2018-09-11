#include <stdio.h>
#include <stdint.h>
#include <sys/resource.h>

int main()
{
  int resources[] = {RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE,
                     RLIMIT_MEMLOCK, RLIMIT_NOFILE, RLIMIT_NPROC, RLIMIT_RSS,
                     RLIMIT_STACK};

  const char *names[] = {"CORE", "CPU", "DATA", "FSIZE",
                         "MEMLOCK", "NOFILE", "NPROC", "RSS",
                         "STACK"};
  int n = sizeof(resources)/sizeof(resources[0]);
  struct rlimit rlim;

  printf("Resource\tSOFT_LIMIT\tHARD_LIMIT\n");
  for(int i=0;i<n;i++){
  		int p = getrlimit(resources[i],&rlim);
  		printf("%s\t%lu\t%lu\n",names[i],rlim.rlim_cur,rlim.rlim_max);
  }
}