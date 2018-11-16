#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	int a[n];
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]==0)
			a[i] = 1;
		else a[i] = -1;
	}
	int max_ending_here=0;
    int max_so_far=0;
    int start =0;
    int end=0;
	for(int i=0;i<n;i++){
		max_ending_here=max_ending_here+a[i];
        if(max_ending_here<0)
        {
            start=i+1; 
            max_ending_here=0;
        } 

        if(max_so_far<=max_ending_here){
            max_so_far=max_ending_here;
            end = i;
        }
        
	}
	cout<<start<<" "<<end<<endl;
}