#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000][1000];

int maxHist(int A[]){
	stack <int> s;
	int i=0,maxArea = 0,j;
	while(i<m){
		if(s.empty() || A[i]>=A[s.top()]){
			s.push(i++);
		}
		else{
			j = s.top();
			s.pop();
			maxArea = max(maxArea,A[j]*(s.empty()?i:(i-s.top()-1)));
		}
	}
	while(!s.empty()){
		j = s.top();
		s.pop();
		maxArea = max(maxArea,A[j]*(s.empty()?i:(i-s.top()-1)));
	}
	return maxArea;
}

void calc(){
	int res = maxHist(a[0]); 
  	for(int i=1;i<n;i++){
  		for(int j=0;j<m;j++){
  			if(a[i][j]){
  				a[i][j]+=a[i-1][j];
  			}
  		}
  		res = max(res,maxHist(a[i]));
  	}
  	cout<<res<<endl;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];

	calc();
}