#include<bits/stdc++.h>
using namespace std;

void getFirst(vector <int> A,int n){
	vector <int> min(n);
	stack <int> s;
	int k;
	s.push(0);
	for(int i=1;i<n;i++){
		k = s.top();
		if(A[i]>=A[k])
			s.push(i);
		else{
			while(!s.empty() && A[i]<A[k]){
				min[k] = i;
				s.pop();
				if(!s.empty())
					k = s.top();
			}
			s.push(i);
		}
		
	}
	while(!s.empty()){
		min[s.top()] = 0;
		s.pop();
	}

	// for(int i=0;i<n;i++){
	// 	cout<<min[i]<<" ";
	// }
	// cout<<endl;

	for(int i=0;i<n;i++){
		if(min[i] > 0){
			cout<<A[i]<<" "<<A[min[i]]<<endl;
			break;
		}
	}
}

int main(){
	int n;
	cin>>n;
	vector <int> A(n);
	for(int i=0;i<n;i++)
		cin>>A[i];

	getFirst(A,n);
}