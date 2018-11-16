#include<bits/stdc++.h>
using namespace std;

int assemblyLine(int A[], int B[], int c, int n){
	int pA[n],pB[n];
	fill_n(pA,n,0);
	fill_n(pB,n,0);
	pA[0]=A[0];
	pB[0]=B[0];
	for(int i=1; i<n; i++){
		pA[i]=max(A[i]+pA[i-1],A[i]+pB[i-1]-c);
		pB[i]=max(B[i]+pB[i-1],B[i]+pA[i-1]-c);
	}
	// for(int i=0; i<n; i++){
	// 	cout<<pA[i]<<" ";	
	// }
	// cout<<endl;
	// for(int i=0; i<n; i++){
	// 	cout<<pB[i]<<" ";	
	// }
	// cout<<endl;
	return max(pA[n-1],pB[n-1]);
}

int main(){
	int n,c;
	cin>>n;
	int A[n],B[n];
	fill_n(A,n,0);
	fill_n(B,n,0);
	cin>>c;
	for(int i=0; i<n; i++){
		cin>>A[i];
	}
	for(int i=0; i<n; i++){
		cin>>B[i];
	}
	cout<<assemblyLine(A,B,c,n)<<endl;
}