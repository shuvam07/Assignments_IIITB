// Brief idea:- Build the directed graph and apply floyd warshall on it, then for given any
// x and y simply print the distance between x and y. This approach works better if there are multiple
// queries of x and y. For just a single query bfs is much better.
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll INF = 1LL*1e9;
ll dist[1000][1000];

void floydWarshall(int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}
int main()
{
    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            dist[i][j] = INF;
        }
    }
    int n;
    cin>>n;
    for(int i = 0; i < n; i++)
    {
        int val;
        cin>>val;
        val = val % n;
        int right = (i + val) % n;
        int left = (i - val + n) % n;
        dist[i][right] = 1;
        dist[i][left] = 1;
    }
    floydWarshall(n);
    int x,y;
    cin>>x>>y;// Assumed 0 based indexing of x and y, if 1-based simply decrement both
    if(dist[x][y] == INF)
    {
        cout<<"\nInfinity";
    }
    else
        cout<<dist[x][y]<<endl;
    return 0;
}
