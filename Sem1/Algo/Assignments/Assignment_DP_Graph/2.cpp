#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair; 

#define INF 1<<29
#define MAX 100005

vector < int > v[MAX];
bool vis[MAX]; 
int steps = 0;

void bfs(int n,int st,int end){
	fill_n(vis,n,0); 
	queue <int> q;
	q.push(st);
	vis[st] =true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		steps++;
		vis[u] = true;
		for(auto i=v[u].begin();i!=v[u].end();i++){
			if(*i == end)
				return;
			if(vis[*i]==false)
				q.push(*i);
		}
	}
	steps = -1;
}	

int main(){
	int n,st,end,val;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>val;
		val = val%n;
		v[i].push_back((i+val)%n);
		v[i].push_back((i-val+n)%n);
	}
	cin>>st>>end;
	bfs(n,st,end);
	cout<<steps<<endl;
}