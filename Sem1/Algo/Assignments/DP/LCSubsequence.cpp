#include<bits/stdc++.h>
using namespace std;

int main(){
	string s1,s2;
	cin>>s1;
	cin>>s2;
	int m=s1.size(),n=s2.size();
	int lcs[m+1][n+1];
	for(int i=0;i<m+1;i++)
		lcs[i][0] = 0;
	for(int i=0;i<n+1;i++)
		lcs[0][i] = 0;

	for(int i=1;i<m+1;i++){
		for(int j=1;j<n+1;j++){
			if(s1[i-1]==s2[j-1]){
				lcs[i][j] = lcs[i-1][j-1]+1;
			}
			else
				lcs[i][j] = max(lcs[i][j-1],lcs[i-1][j]);
		}
	}
	cout<<lcs[m][n]<<endl;
	int len = lcs[m][n];
	char l[len+1];
	l[len+1] = '\0';

	int i=m,j=n;
	while(i>0 && j>0){
		if(s1[i-1]==s2[j-1]){
			l[len-1] = s1[i-1];
			i--,j--,len--;
		}
		else if(lcs[i-1][j] > lcs[i][j-1]){
			i--;
		}
		else
			j--;
	}
	cout<<l<<endl;
}