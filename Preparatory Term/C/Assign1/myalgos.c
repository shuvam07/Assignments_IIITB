#include "myalgos.h"

void swap(int *a,int *b){
	int c = *a;
	*a = *b;
	*b = c;
	
}

int partition(int *arr,int low,int high){
	int pivot = arr[high];
	int i = (low - 1),j; 

    for (j = low; j <= high- 1; j++)
    {
     
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return (i + 1);
}

void quickSort(int *a,int low,int high){
	if(low<high){
		int p = partition(a,low,high);
		quickSort(a,low,p-1);
		quickSort(a,p+1,high);
	}
}

void quick_sort(int *a,int n){
	quickSort(a,0,n-1);
}


void insertion_sort(int *arr,int n){
	int i, key, j;
    for (i = 1; i < n; i++)
    {
       key = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
    }
}