#include<bits/stdc++.h>
using namespace std;
int main()
 {
    int t;
	cin>>t;
	while(t--){
	    	int n,min_v=INT_MAX;
        	cin>>n;
        	vector <int> a(n);
        	for(int i=0;i<n;i++)
        		cin>>a[i];
        	sort(a.begin(),a.end());
        	for(int i=1;i<n;i++)
        		min_v=min(min_v,a[i]-a[i-1]);
        	cout<<min_v<<endl;
	}
	return 0;
}
