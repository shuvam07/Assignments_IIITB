#include "datadef.h"
#include "myutils.h"
#include <stdlib.h>
#include <stdio.h>

int* load_generator(){

	int* a = (int*)malloc(N * sizeof(int));

	for(int i=0;i<N;i++){
		int val  = rand() % MAX_RANGE +1 ;
		a[i] = val;
	}

	return a;
}

void print_arr(int* a,int n){

	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");;
}

