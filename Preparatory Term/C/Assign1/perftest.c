#include "myutils.h"
#include "myalgos.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "datadef.h"

int main()
{
	int n = N;

	int *data1 = load_generator();
	int *data2 = (int*)malloc(n * sizeof(int));

	clock_t t1;
	clock_t t2;

	for(int i=0;i<N;i++){
		data2[i]=data1[i];
	}

	
    t1 = clock();
	quick_sort(data1,n);
	t1 = clock() - t1;
	double time_taken = ((double)t1)/CLOCKS_PER_SEC;
	// printf("Sorted Array :\n");
	// print_arr(data1,n);
	printf("Time Elapsed in secs %f\n",time_taken);

	t2 = clock();
	insertion_sort(data2,n);
	t2 = clock() - t2;
	time_taken = ((double)t2)/CLOCKS_PER_SEC;
	// printf("Sorted Array :\n");
	// print_arr(data2,n);
	printf("Time Elapsed in secs %f\n",time_taken);

	return 0;
}