#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	int price[n+1];
	for(int i=0;i<n;i++){
		cin>>price[i];
	}
	int dp[n+1],maxV=INT_MIN;
	dp[0] = 0;
	for(int i=1;i<=n;i++){
		maxV=INT_MIN;
		for(int j=0;j<i;j++){
			maxV = max(maxV,price[j]+dp[i-j-1]);
		}
		dp[i] = maxV;
	}
	cout<<dp[n]<<endl;
}