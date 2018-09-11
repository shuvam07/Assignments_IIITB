#include<bits/stdc++.h>
using namespace std;


int merge(vector <int> &a,int l,int m,int r){
	vector <int> temp;
	int i=l,j=m+1;
	int cnt = 0;
	while(i<=m && j<=r){
		if(a[i]>a[j]){
			cnt+= (m-i+1);
			temp.push_back(a[j++]);
		}
		else
			temp.push_back(a[i++]);
	}
	while(i<=m){
		temp.push_back(a[i++]);
	}
	while(j<=r){
		temp.push_back(a[j++]);
	}
	for(int p=l;p<=r;p++){
		a[p] = temp[p-l];
	}
	return cnt;
}

int inversion(vector <int> &a,int l,int r){
	int cnt=0;
	if(l<r){
		int m = (l+r)/2;
		cnt = inversion(a,l,m);
		cnt+= inversion(a,m+1,r);
		cnt+= merge(a,l,m,r);
	}
	return cnt;
}

int main(){
	int n;
	cin>>n;
	vector <int> a(n);
	for(int i=0;i<n;i++)
		cin>>a[i];

	cout<<inversion(a,0,n-1)<<endl;
}