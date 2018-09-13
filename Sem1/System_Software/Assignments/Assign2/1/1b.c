#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

// http://www.informit.com/articles/article.aspx?p=23618&seqNum=14


void timer_handler (int signum)
{
	static int count = 0;
	printf ("timer expired %d times\n", ++count);
}

int main(){
	struct sigaction sa;
	struct itimerval timer;

	/* Install timer_handler as the signal handler for SIGALRM. */
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &timer_handler;
	sigaction (SIGVTALRM, &sa, NULL);

	/* Configure the timer to expire after 10 sec 10 microsec... */
	timer.it_value.tv_sec = 10;
	timer.it_value.tv_usec = 10;
	/* ... and every 10 sec 10 microsec after that. */
	timer.it_interval.tv_sec = 10;
	timer.it_interval.tv_usec = 10;
	/* Start a real timer. It counts down whenever this process is
	  executing. */
	setitimer (ITIMER_VIRTUAL, &timer, NULL);
   
    /* Do busy work. */
	while (1);
}