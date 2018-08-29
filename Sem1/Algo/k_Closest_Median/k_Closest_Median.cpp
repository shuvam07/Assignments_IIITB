#include <bits/stdc++.h>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[],int l,int r){
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
            return pos;
        else if((pos-l+1)>k){
            return kth_Small(a,l,pos-1,k);
        }
        else
            return kth_Small(a,pos+1,r,k-pos+l-1);
    }
}

int main(){
	int n,k;
	cin>>n>>k;
	int a[n];
	vector <int> v;
	vector <int>::iterator it;
	for(int i=0;i<n;i++){
		cin>>a[i];
		v.push_back(a[i]);
	}
	//int med = getMedian(A,n);
	int med = a[kth_Small(a,0,n-1,n/2+1)];
	cout<<"K closest to median "<<med<<endl;
	for(int i=0;i<n;i++){

		a[i]=abs(a[i]-med);

		//cout<<a[i]<<" ";
	}
	//cout<<endl;


	int l = kth_Small(a,0,n-1,k+1);
	// cout<<"pos "<<l<<endl;

	// for(int i=0;i<n;i++)
	// 	cout<<a[i]<<" ";

	// cout<<endl;


	for(int i=0;i<l;i++){
		it  = find(v.begin(),v.end(),a[i]+med);
		if(it!=v.end()){
			cout<<a[i]+med<<" ";
			v.erase(it);
		}
		else {
			it  = find(v.begin(),v.end(),med-a[i]);
			if(it!=v.end()){
				cout<<med-a[i]<<" ";
				v.erase(it);
			}
		}
	}
	cout<<endl;
}