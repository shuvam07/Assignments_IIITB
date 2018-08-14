/* Generated 1000 bit number and computed fibonacci of that number modulo 1000000007 */ 



#include <bits/stdc++.h>
using namespace std;

#define N 10000
#define mod 1000000007
#define ll long long int

void mult(ll F[2][2], ll M[2][2]){
	ll x = F[0][0]*M[0][0] + F[0][1]*M[1][0];
	ll y = F[0][0]*M[0][1] + F[0][1]*M[1][1];
	ll z = F[1][0]*M[0][0] + F[1][1]*M[1][0];
	ll w = F[1][0]*M[0][1] + F[1][1]*M[1][1];

	F[0][0] = x%mod;
	F[0][1] = y%mod;
	F[1][0] = z%mod;
	F[1][1] = w%mod;
}

ll power(vector <int> a, ll A[2][2]){
	int i=a.size()-1;
	ll y[2][2] = {{1,0},{0,1}};
	while(i>=0){
		//cout<<a[i]<<endl;
		if(a[i]) 
			mult(y,A);
		mult(A,A);
		i--;
	}
	return y[0][1];
}

ll fib(vector <int> a){
	ll A[2][2] = {{1,1},{1,0}};
	return power(a,A);
}

int main() {
	vector <int> a;
	int i=0;
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		a.push_back(s[i]-48);
	}
	cout<<fib(a)<<endl;
	return 0;
}
