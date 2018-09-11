#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *doStuff(int *i){
	printf("I am thread %d\n",(*i+1));
	return NULL;
}
int main() {
    pthread_t thr;
	size_t i;

	for(i=0;i<3;i++) {
	   pthread_create(&thr, NULL , (void *)(&doStuff) , &i);
	   sleep(2);
	}
}