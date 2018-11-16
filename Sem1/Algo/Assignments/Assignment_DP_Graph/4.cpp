#include<bits/stdc++.h>
using namespace std;
 
#define MAX 100000
#define MAX1 200000
#define inf 1000000000
#define mod 1000000007
#define ll long long
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
typedef tree< pair<int,int>,null_type, less< pair<int,int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
 
ordered_set BIT[MAX1+5];
vector<int>graph[MAX+5];
map<int,int>compress;
int A[MAX+5],B[MAX+5];
ll ans;
 
void add(int x,int node,int val)
{
    for(;x<=MAX1;x+=x&-x)
        BIT[x].insert({val,node});
}
void rem(int x,int node,int val)
{
    for(;x<=MAX1;x+=x&-x)
        BIT[x].erase({val,node});
}
int get(int x,int y)
{
    int ret=0;
    for(;x>0;x-=x&-x)
        ret+=BIT[x].order_of_key({y,0});
    return ret;
}
void dfs(int u,int p)
{
    ans+=get(A[u]-1,B[u]);
    add(A[u],u,B[u]);
    for(auto z:graph[u])
        if(z!=p)
            dfs(z,u);
    rem(A[u],u,B[u]);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int i,u,v,w,N;
	cin>>N;
	for(i=0;i<N-1;++i)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(i=1;i<=N;++i)
    {
        cin>>A[i];
        compress[A[i]];
    }
    for(i=1;i<=N;++i)
    {
        cin>>B[i];
        compress[B[i]];
    }
    i=0;
    for(auto &z:compress)
        z.second=++i;
    for(i=1;i<=N;++i)
    {
        A[i]=compress[A[i]];
        B[i]=compress[B[i]];
    }
    dfs(1,0);
    cout<<ans;
 
    return 0;
}