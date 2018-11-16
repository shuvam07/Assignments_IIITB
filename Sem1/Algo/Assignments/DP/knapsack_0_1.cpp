#include<bits/stdc++.h>
using namespace std;



int main(){
	int n,W;
	cin>>n>>W;
	int val[n];
	int wt[n];
	int T[n+1][W+1];
	for(int i=0;i<n;i++)
		cin>>val[i];
	for(int i=0;i<n;i++)
		cin>>wt[i];

	for(int i=0;i<=n;i++)
		T[i][0] = 0;

	for(int i=0;i<=W;i++)
		T[0][i] = 0;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=W;j++){
			if(j>=wt[i-1]){
				T[i][j] = max(T[i-1][j],val[i-1]+T[i-1][j-wt[i-1]]);
			}
			else
				T[i][j] = T[i-1][j];
		}
	}

	cout<<T[n][W]<<endl;

	int w = W;
	int res = T[n][W];
	for(int i=n;i>0 && res>0;i--){
		if(T[i][w]==T[i-1][w])
			continue;
		else{
			cout<<wt[i-1]<<" ";
			res -= val[i-1];
			w -= wt[i-1];
		}
	}
	cout<<endl;
}