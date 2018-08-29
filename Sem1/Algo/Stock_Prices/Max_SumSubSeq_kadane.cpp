#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
	    
	    	int n,i,j,sum=0,maxSum=INT_MIN;
	    	
        	cin>>n;
        	vector <int> a(n);
        	
        	for(i=0;i<n;i++)
        		cin>>a[i];

		for(i=0;i<n;i++){
			sum+=a[i];
			maxSum = max(maxSum,sum);
			if(sum<0) sum=0;		
		}
		cout<<maxSum<<endl;
	}
}
