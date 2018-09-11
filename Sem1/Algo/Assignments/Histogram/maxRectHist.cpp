#include<bits/stdc++.h>
using namespace std;

int maxRectHist(vector <int> A,int n){
	stack <int> s;
	int i=0,maxArea = 0,j;
	while(i<n){
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
int main(){
	int n;
	cin>>n;
	vector <int> A(n);
	for(int i=0;i<n;i++)
		cin>>A[i];

	cout<<maxRectHist(A,n)<<endl;
}