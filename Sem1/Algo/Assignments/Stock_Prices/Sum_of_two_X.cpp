#include<bits/stdc++.h>
using namespace std;
int main()
 {
     int t;
	cin>>t;
	while(t--){
	    	int n,x,flag=1;
        	cin>>n>>x;
        	vector <int> a(n);
        	for(int i=0;i<n;i++)
        		cin>>a[i];
        	sort(a.begin(),a.end());
        	int l=0,r=n-1;
        	while(l<r){
        		int sum=a[l]+a[r];
        		if(sum==x){
        			cout<<"Yes"<<endl;
        			flag=0;
        			break;
        		}
        		sum<x?l++:r--;
        	}
        	if(flag)
        	cout<<"No"<<endl;
	}
	return 0;
}
