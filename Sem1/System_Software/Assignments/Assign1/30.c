#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<sched.h>

int main()
{
	/* need to use cron */
	char command[100] = "echo hello";
	system(command);
    return 0;
}