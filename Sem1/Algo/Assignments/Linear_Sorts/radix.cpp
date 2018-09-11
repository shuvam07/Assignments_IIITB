#include<bits/stdc++.h>
using namespace std;

void counting(int A[],int n,int m){
	int B[10] = {0};
	for(int i=0;i<n;i++){
		B[(A[i]/m)%10]++;
	}
	for(int i=1;i<10;i++){
		B[i]=B[i]+B[i-1];
	}

	int res[n];
	for (int i = 0; i < n; ++i)
	{
		res[B[(A[i]/m)%10]-1] = A[i];
		B[(A[i]/m)%10]--;
	}
	for (int i = 0; i < n; ++i)
	{
		A[i] = res[i];
	}
}

int main(){
	int n,mx=INT_MIN;
	cin>>n;
	int A[n];
	for(int i=0;i<n;i++){
		cin>>A[i];
		mx = max(mx,A[i]);
	}
	for(int m=1;mx/m>0;m*=10)
		counting(A,n,m);

	for(int i=0;i<n;i++)
		cout<<A[i]<<endl;
}