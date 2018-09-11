#include <bits/stdc++.h>
using namespace std;
int main(){
	int data;
	int k=10,v,i=0,cnt=0;
	//cin>>k;
	ifstream read("data.txt");
	int a[2*k];
    while(read>>data && cnt<k){
        cnt++;
        a[i]=data;
        cout<<a[i++]<<" ";
    }
}
