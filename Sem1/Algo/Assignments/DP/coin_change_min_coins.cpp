#include<bits/stdc++.h>
using namespace std;

void print(int coins[],int k,int a[]){
	
	while(k!=0){
		if(coins[k]!=-1){
			cout<<a[coins[k]]<<" ";
			k-=a[coins[k]];
		}
		else break;
	}
	cout<<endl;
}

int main(){
	int n,k;
	cin>>n>>k;
	int a[n];
	int total[k+1];
	int coins[k+1];
	for(int i=0;i<k+1;i++)
		total[i] = INT_MAX-1;         // ---> -1 since after adding 1 to infinty it is not required to overflow
	for(int i=0;i<k+1;i++)
		coins[i] = -1;
	//memset(total,INT_MAX,sizeof(total)); ------>> doesnt work since memset 2nd arg takes size of 1 byte only so INT_MAX overflows
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	total[0] = 0;
	coins[0] = 0;
	for(int j=0;j<n;j++){
		for(int i=1;i<k+1;i++){
			if(i>=a[j] && total[i-a[j]]+1 <= total[i]){
				total[i] = min(total[i-a[j]]+1,total[i]);
				coins[i] = j;
			}
		}
	}
	// print(coins,k,a);
	if(total[k]==INT_MAX-1)
		cout<<-1<<endl;
	else
		cout<<total[k]<<endl;
}