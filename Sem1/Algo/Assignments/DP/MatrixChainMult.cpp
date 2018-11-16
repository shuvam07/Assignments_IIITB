#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	int a[n];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	int dp[n][n];
	for(int i=1;i<n;i++)
		dp[i][i] = 0;
	for(int l=2;l<n;l++){
		for(int i=1;i<n-l+1;i++){
			int j = i+l-1;
			dp[i][j] = INT_MAX;
			for(int k=i;k<=j-1;k++){
				int q = dp[i][k]+dp[k+1][j]+a[i-1]*a[k]*a[j];
				if(q<dp[i][j])
					dp[i][j]=q;
			}
		}
	}
	cout<<dp[1][n-1]<<endl;
}