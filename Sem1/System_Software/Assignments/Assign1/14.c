#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat s;	
	stat(argv[1],&s);
	printf("%lu",s.st_dev);
}
