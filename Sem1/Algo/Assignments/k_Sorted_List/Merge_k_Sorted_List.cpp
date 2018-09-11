#include <bits/stdc++.h>
using namespace std;


vector <int>  merge(vector<int> a,vector <int> b){
	
	int l1 = a.size(),l2=b.size(),i=0,j=0,k=0;
	
	// for(i=0;i<l1;i++){
	// 	cout<<a[i]<<" ";
	// }
	// cout<<endl;
	// for(i=0;i<l2;i++){
	// 	cout<<b[i]<<" ";
	// }
	// cout<<endl;
	vector <int> temp(l1+l2);
	i=0;
	while(i<l1 && j<l2){
		temp[k++] = (a[i]<b[j])?a[i++]:b[j++];
	}
	while(i<l1)
		temp[k++]=a[i++];
	while(j<l2)
		temp[k++]=b[j++];
	
	// for(i=0;i<l1+l2;i++){
	// 	cout<<temp[i]<<" ";
	// }
	// cout<<endl;
	return temp;
}

int main() {
	int n,k,l,val,i;
	cin>>k;
	vector <vector<int> > a(k);
	for(i=0;i<k;i++){
		cin>>l;
		a[i] = vector <int>();
		for(int j=0;j<l;j++){
			cin>>val;
			a[i].push_back(val);
		}
	}
	for(i=0;i<k;i++){
		for(int j=0;j<a[i].size();j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	int j;
	
	while(k>1){
		for(j=0;j<k;j+=2){
				if(j+1!=k)
					a[j/2] = merge(a[j],a[j+1]);
				else
					a[j/2] = a[k-1];
		}
		if(k%2==1)
			k=k/2+1;
		else k=k/2;
	}
	for(i=0;i<a[0].size();i++)
	{
		cout<<a[0][i]<<" ";
	}
	
}
