#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000][1000];
int res = INT_MIN;

int kadane(int temp[],int n,int &st,int &end){
	int i,sum=0,maxSum=INT_MIN,currS=0;
	for(i=0;i<n;i++){
			sum+= temp[i];
			if(sum<0){
				sum=0;
				currS = i+1;
			}
			if(sum>maxSum){
				maxSum = sum;
				end = i;
				st = currS;
			}
					
	}
	return maxSum;
}

void calc(){
	int maxSum,lb,rb,ub,lowb;
	int temp[n];
	for(int l=0;l<m;l++){
		for(int i=0;i<n;i++)
			temp[i]=0;
		for(int r=l;r<m;r++){
			for(int i=0;i<n;i++)
				temp[i]+=a[i][r];
			int st=-1,end=-1;
			int val = kadane(temp,n,st,end);
			if(val>res){
				res = val;
				lb=l;
				rb=r;
				ub = st;
				lowb = end;
			}
		}

	}
	cout<<res<<endl;
	cout<<lb<<" "<<ub<<endl;
	cout<<lowb<<" "<<rb<<endl;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];

	calc();
}