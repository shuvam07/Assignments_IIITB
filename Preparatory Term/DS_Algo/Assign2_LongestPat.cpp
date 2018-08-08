#include<bits/stdc++.h>

using namespace std;

#define size 256
#define mod 101

string maxPat="";


bool search(string pat, string txt, int k)
{
	int M = pat.length();
	int N = txt.length();
	int i, j;
	int p = 0; 
	int t = 0; 
	int h = 1;

	for (i = 0; i < M-1; i++)
		h = (h*size)%mod;

	for (i = 0; i < M; i++)
	{
		p = (size*p + pat[i])%mod;
		t = (size*t + txt[i])%mod;
	}
	int cnt=0;
	for (i = 0; i <= N - M; i++)
	{
		if ( p == t )
		{
			for (j = 0; j < M; j++)
			{
				if (txt[i+j] != pat[j])
					break;
			}

			if (j == M){
				cnt++;
			}
		}
		if ( i < N-M )
		{
			t = (size*(t - txt[i]*h) + txt[i+M])%mod;
			t = (t + mod);
		}
	}
	if(cnt == k){
		maxPat = pat;
		return true;
	}
	return false;
}

void longestPat(string txt,int k){
	int l=1,h=txt.length()-k;
	while(l<h){
		int mid = (l+h)/2;
		string pat = txt.substr(0,mid);
		if(search(pat,txt,k)){
			l=mid+1;
		}
		else
			h=mid-1;
	}
	
}

int main()
{
	string txt,pat;
	int k;
	cin>>txt;
	cin>>k;
	longestPat(txt,k);
	if(maxPat==""){
		cout<<"Not Found any"<<endl;
	}
	else
		cout<<maxPat<<endl;
	return 0;
}

