#include<bits/stdc++.h>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void random(int a[],int l,int r){
    int n = (r-l+1);
    int x = l+(rand()%n);
    swap(&a[x],&a[x]);
    
}
int partition(int a[],int l,int r){
    random(a,l,r);
    int pivot = a[r];
    int i=l;
    for(int j=l;j<r;j++){
        if(a[j]<=pivot){
            swap(&a[i],&a[j]);
            i++;
        }
    }
    swap(&a[i],&a[r]);
    return (i);
}
int kth_Small(int a[],int l,int r,int k){
    
    if(k>0 && (r-l+1)>=k){
        int pos = partition(a,l,r);
        //printf("pos %d\n",pos);
        if((pos-l+1)==k)
            return a[pos];
        else if((pos-l+1)>k){
            return kth_Small(a,l,pos-1,k);
        }
        else
            return kth_Small(a,pos+1,r,k-pos+l-1);
    }
}
int main()
 {
	//code
	int t;
	cin>>t;
	while(t--){
	    int n,k;
	    cin>>n;
	    int a[n];
	    for(int i=0;i<n;i++){
	        cin>>a[i];
	    }
	    cin>>k;
	    cout<<kth_Small(a,0,n-1,k)<<endl;
	}
	return 0;
}
