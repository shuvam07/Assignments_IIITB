#include<bits/stdc++.h>
using namespace std;
int main()
 {
    int t;
	cin>>t;
	while(t--){
	    
	    	int n,min_v=INT_MAX,prof=INT_MIN,min_i=0,l,i,j;
	    	
        	cin>>n>>l;
        	vector <int> a(n);
        	
        	for(i=0;i<n;i++)
        		cin>>a[i];
        		
        	for(i=0;i<l;i++){
        	    if(a[i]<a[min_i])
        	        min_i=i;
        	}
        	for(j=i-1;j<n;j++){
        	    if((a[j]-a[min_i])>prof)
        	        prof = a[j]-a[min_i];
        	   
        	    if(a[j-(l-1)]<a[min_i])
        	        min_i=j-(l-1);
        	       
        	}
        	cout<<prof<<endl;
	}
        	
	return 0;
}
