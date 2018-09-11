#include<bits/stdc++.h>
using namespace std;
int main()
 {
    int t;
	cin>>t;
	while(t--){
	    
	    	int n,min_v=INT_MAX,prof=INT_MIN;
	    	
        	cin>>n;
        	vector <int> a(n);
        	
        	for(int i=0;i<n;i++)
        		cin>>a[i];
        		
        	for(int i=0;i<n;i++){
        	    if((a[i]-min_v) > prof){
        		    prof=a[i]-min_v;
        		}
        		if(a[i]<min_v)
        		    min_v=a[i];
        		
        	}
        		
        	cout<<prof<<endl;
	}
        	
	return 0;
}
