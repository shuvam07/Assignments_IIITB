#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	int lis[n];
	for(int i=0;i<n;i++){
		lis[i] = 1;
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			if(a[i]>=a[j] && lis[j]+1>lis[i])
				lis[i] = lis[j] + 1;
		}
	}
	cout<<lis[n-1]<<endl;
}