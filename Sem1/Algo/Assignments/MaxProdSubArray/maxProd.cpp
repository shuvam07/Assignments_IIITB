#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	vector <int> a(n);
	for(int i=0;i<n;i++)
		cin>>a[i];

	int prev_max_prod = a[0];
	int prev_min_prod = a[0];
	int curr_max_prod = a[0];
	int curr_min_prod = a[0];
	int ans = a[0];

	for(int i=1;i<n;i++){
		curr_max_prod = max(prev_max_prod*a[i],max(prev_min_prod*a[i],a[i]));
		curr_min_prod = min(prev_max_prod*a[i],min(prev_min_prod*a[i],a[i]));
		ans = max(ans,curr_max_prod);
		prev_max_prod = curr_max_prod;
		prev_min_prod = curr_min_prod;
	}
	cout<<ans<<endl;
}