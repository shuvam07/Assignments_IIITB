#include<bits/stdc++.h>
using namespace std;
int main()
 {
    int t;
	cin>>t;
	while(t--){
	    
	    	int n,min_v=INT_MAX,prof=INT_MIN,min_i=0,l,i,j;
	    	
	    	deque <int> q;
	    	
        	cin>>n>>l;
        	vector <int> a(n);
        	
        	for(i=0;i<n;i++)
        		cin>>a[i];
        		
            	q.push_back(0);
        	for(j=1;j<n;j++){
        	    if((a[j]-a[min_i])>prof)
        	        prof = a[j]-a[min_i];
        	   
        	   while(!q.empty() && a[q.back()]>a[j])
        	        q.pop_back();
        	        
        	   q.push_back(j);
        	    
        	   if((j+1-min_i)>=l){
        	   
        	     min_i=q.front();
        	     q.pop_front();
        	   }
		   cout<<prof<<" "<<min_i<<endl;
        	   
        	}
        		
        	cout<<prof<<endl;
	}
        	
	return 0;
}
