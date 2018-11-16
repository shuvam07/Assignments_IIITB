#include<bits/stdc++.h>
#define pb push_back
using namespace std;

struct Node
{
    int no;
    int weight;
    int max_val = INT_MIN;
    int max_child_weight = INT_MIN;
};
vector <Node> adj[1000];
Node nodes[1000];
bool visited[1000];


void dfs(Node u)
{
    visited[u.no] = true;
    bool flag = false;
    for(int i = 0; i < adj[u.no].size(); i++)
    {
        Node n = adj[u.no][i];
        if(!visited[n.no]){
            dfs(n);
            flag = true;
        }
    }

    if(!flag)
    {
        nodes[u.no].max_child_weight = nodes[u.no].weight;
        nodes[u.no].max_val = nodes[u.no].weight;
    }

    for(int i = 0; i < adj[u.no].size(); i++)
    {
        Node x = adj[u.no][i];
        nodes[u.no].max_child_weight = max(nodes[x.no].max_val,nodes[u.no].max_child_weight);
    }
    nodes[u.no].max_val = max(nodes[u.no].weight,nodes[u.no].max_child_weight);
}

int main()
{
    int n,m;
    cin>>n;
    for(int i = 0; i < n; i++)
    {
        nodes[i].no = i;
        cin>>nodes[i].weight;
        nodes[i].max_val = nodes[i].weight;
    }
    cout<<"\nEnter the number of Edges : ";
    cin>>m;
    for(int i = 0; i < m; i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(nodes[v]);
    }
    for(int i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            dfs(nodes[i]);
        }
    }
    int ans = INT_MIN;
    for(int i = 0; i < n; i++)
    {
        //cout<<nodes[i].max_child_weight<<endl;
        ans = max(ans, nodes[i].max_child_weight - nodes[i].weight);
    }
    cout<<ans<<endl;
    return 0;
}
