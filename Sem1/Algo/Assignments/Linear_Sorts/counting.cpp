#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,mx=INT_MIN;
	cin>>n;
	vector <int> A(n);
	for(int i=0;i<n;i++){
		cin>>A[i];
		mx=max(mx,A[i]);
	}
	vector <int> B(mx+1,0);
	for(int i=0;i<n;i++){
		B[A[i]]++;
	}
	for(int i=1;i<=mx;i++){
		B[i]=B[i]+B[i-1];
	}

	vector <int> res(n,0);
	for (int i = 0; i < n; ++i)
	{
		res[B[A[i]]-1] = A[i];
		B[A[i]]--;
	}
	for (int i = 0; i < n; ++i)
	{
		cout<<res[i]<<" ";
	}
	cout<<endl;
}