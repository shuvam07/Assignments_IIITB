#include <bits/stdc++.h>
using namespace std;

bool check(vector <int> v){
	int cnt = 1,i=0,maxCnt=0,n=v.size(),pow=1;
	while(i<n){
		while(i+1 < n && (v[i]==v[i+1])){
			maxCnt++;
			if(maxCnt > cnt)
				return 0;
			i++;
		}
		pow = 2*pow;
		cnt = max(pow,(maxCnt+1)*2);
		i++;
	}
	return 1;
}

int main() {
	int n;
	cin>>n;
	vector <int> v(n);
	for(int i=0;i<n;i++){
		cin>>v[i];
	}
	cout<<check(v)<<endl;
	return 0;
}
