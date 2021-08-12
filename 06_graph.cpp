#include <vector>
#include <climits>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXN 5003
typedef pair<int, int> P;

int cmp[2002][2002];
int N, M;
struct Edge{
  int to, cost;
};

int dist[MAXN];
vector<Edge> G[MAXN];
int ans[MAXN];

void dijk(const int &start)
{
  priority_queue<P, vector<P>, greater<P> > que;
  fill(dist, dist+MAXN, INT_MAX);
  que.push(P{0, start});
  dist[start] = 0;

  while (!que.empty()){
    P p = que.top(); que.pop();
    // cout << p.first << " " << dist[p.second] << " ";
    int v = p.second;
    if (p.first > dist[v]) continue;

    for (Edge &e: G[v]){
        // cout << e.to  <<" " << dist[e.to] << " " << dist[p.second] + e.cost << endl;
      if ( dist[v] + e.cost == dist[e.to] ) {
        ans[e.to] += ans[v];
      }
      if ( dist[v] + e.cost < dist[e.to] ) {
        dist[e.to] = dist[v] + e.cost;
        // cout << dist[e.to] << endl;
        ans[e.to] = ans[v];
        que.push(P{dist[e.to], e.to});
      }

    }

  }
}
int main()
{
  cin >> N >> M;
  int u, v, w;
  for (int i=0;i<M;i++)
  {
    cin >> u >> v >> w;
    if (cmp[u][v] == 0 || cmp[u][v] > w){
      G[u].push_back(Edge{v, w});
      cmp[u][v] = w;
    }
  }
  // cout << G[1][0].cost << endl; 
  for (int i=0;i<N;i++) ans[i]=0;
  ans[1] = 1;
  dijk(1);
  if (dist[N] == INT_MAX) cout << "No answer" << endl;
  else cout << dist[N] << " " << ans[N] << endl;
  return 0;
}


