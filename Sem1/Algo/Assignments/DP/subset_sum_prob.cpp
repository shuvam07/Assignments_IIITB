#include<bits/stdc++.h>
using namespace std;

bool T[1001][1001];

void display(vector<int> &res){
	for(int i=0;i<res.size();i++){
		cout<<res[i]<<" ";
	}
	cout<<endl;
}

void printSubsets(int a[],int n,int sum,vector<int> res){

	if(sum==0){
        display(res);
        return;
    }
    if(sum<0) 
    	return;

    if(T[n][sum]){

        printSubsets(a,n-1,sum,res);
        res.push_back(a[n-1]);
        printSubsets(a,n-1,sum-a[n-1],res);
        res.pop_back();
        
    }

}

int main(){
	int n,sum;
	cin>>n>>sum;
	int a[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	// bool T[n+1][sum+1];

	for(int i=0;i<=n;i++)
		T[i][0] = true;

	for(int i=1;i<=sum;i++)
		T[0][i] = false;

	for(int i=1;i<=n;i++){
		for(int j=0;j<=sum;j++){
			if(j<a[i-1])
				T[i][j] = T[i-1][j];
			else
				T[i][j] = T[i-1][j] || T[i-1][j-a[i-1]];
		}
	}

	cout<<T[n][sum]<<endl;

	vector<int> res;
	printSubsets(a,n,sum,res);
}