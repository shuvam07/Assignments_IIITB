#include <bits/stdc++.h>
using namespace std;

int findMedian(int a[],int n){
	sort(a,a+n);
	return a[n/2];
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[],int l,int r,int x){

	int i;
	for(i=l;i<r;i++){
		if(a[i]==x)
			break;
	}
	swap(&a[i],&a[r]);
    int pivot = a[r];
    i=l;
    for(int j=l;j<r;j++){
        if(a[j]<=pivot){
            swap(&a[i],&a[j]);
            i++;
        }
    }
    swap(&a[i],&a[r]);
    return (i);
}

int kthSmallest(int a[],int l, int r,int k){

	if(k>=0 && k<=(r-l+1)){

		int n=r-l+1,i;
		int median[(n+4)/5];
		for(i=0;i<n/5;i++){
			median[i] = findMedian(a+l+i*5,5);
		}
		if(i*5 < n){
			median[i] = findMedian(a+l+i*5,n%5);
		}

		int medofmed = (i==1)?median[0]:kthSmallest(median,l,i-1,i/2);
		int pos = partition(a,l,r,medofmed);
		if(pos-l == k-1)
			return a[pos];
		if(pos-l > k-1)
			return kthSmallest(a,l,pos-1,k);
		else
			return kthSmallest(a,pos+1,r,k-pos+l-1);

	}

	return INT_MAX;
}

int main(){

	int n,k;
	cin>>n>>k;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<kthSmallest(a,0,n-1,k)<<endl;
}