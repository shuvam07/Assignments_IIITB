#include <stdio.h>
#include <sys/types.h>
#include <sched.h>

 
int main()
{
    printf("Max = %d\n",sched_get_priority_max(CONFIG_PREEMPT_RT));
 	printf("Min = %d\n",sched_get_priority_min(CONFIG_PREEMPT_RT));
    return 0;
}