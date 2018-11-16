#include <bits/stdc++.h>
using namespace std;

const int N = 100 , INF = (int)2e9;
int n,imbalance[N+2];

int nodes, F[N+2][N+2], C[N+2][N+2], xf[N+2], ht[N+2], nxt[N+2];

inline void pushExcess(int u,int v) {
  int df = min(xf[u] , C[u][v] - F[u][v]);
  F[u][v] += df , F[v][u] -= df;
  xf[u] -= df, xf[v] += df;
}

inline void relabelNode(int u){
  int min_ht = 2*nodes;
  for(int v=0;v<nodes;v++)
    if( C[u][v] > F[u][v] ) min_ht = min(min_ht,ht[v]);
  ht[u] = min_ht+1;
}

void discharge(int u) {
  while( xf[u] > 0 ) {
    int v = nxt[u];
    if( v < nodes ) { // push excess flow downhill
      if( C[u][v] > F[u][v] and ht[u] > ht[v] ) pushExcess(u,v);
      else ++nxt[u];
    } else { // relabel and rewind
      relabelNode(u); nxt[u] = 0;
    }
  }
}

int GoldbergTarjan(int src=0,int sink=n+1) {
  fill(xf,xf+nodes,0);
  fill(ht,ht+nodes,0);
  fill(nxt,nxt+nodes,0);
  
  int list[nodes-2];
  for(int i=0,j=0;i<nodes;i++) {
    if( i==src or i==sink ) continue;
    list[j++] = i;
  }
  
  ht[src] = nodes; xf[src] = INF;
  for(int i=0;i<nodes;i++)
    if(i != src) pushExcess(src,i);
  
  int index = 0;
  while( index < nodes-2 ) {
    int u = list[index];
    int prev_ht = ht[u];
    discharge(u);
    if( ht[u] > prev_ht ) { // move to front
      for(int j=index-1;index>0;index--,j--)
	list[index] = list[j];
      list[0] = u;
    } else {
      index++;
    }
  }
  
  int maxFlow = 0;
  for(int v=0;v<nodes;v++)
    maxFlow += F[src][v];
  return maxFlow;
}

void constructGraph(int guess) {
  nodes = n+2;
  memset(F,0,sizeof F);
  memset(C,0,sizeof C);
  int src = 0, sink = n+1;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++) {
      C[i][j] = C[j][i] = guess;
    }
  for(int i=1;i<=n;i++)
    if( imbalance[i] > 0 ) C[src][i] = imbalance[i];
    else if( imbalance[i] < 0 ) C[i][sink] = -imbalance[i];
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  
  cin >> n;
  int totalFlow = 0 , checkFeasible = 0;
  for(int i=1;i<=n;i++) {
    cin >> imbalance[i];
    if( imbalance[i] > 0 ) totalFlow += imbalance[i];
    if( imbalance[i] < 0 ) checkFeasible -= imbalance[i];
  }
  assert(totalFlow == checkFeasible);
  
  imbalance[0] = imbalance[n+1] = 0;
  
  int lo = 0 ,
    hi = max( *max_element(imbalance+1,imbalance+n+1) ,
	      -*min_element(imbalance+1,imbalance+n+1) );
  while( lo < hi ) {
    int guess = (lo + hi)/2;
    constructGraph(guess);
    int flow = GoldbergTarjan();
    if( totalFlow == flow ) hi = guess;
    else lo = guess+1;
  }
  cout << lo << '\n';
  
  return 0;
}