// https://acm.hdu.edu.cn/showproblem.php?pid=1874
// dijkstra
// 31MS	1476K

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 205;
vector<pair<int, int>> E[maxn];

int n, m;
int dist[maxn], inq[maxn];
const int INF = 0x7fffffff;
void init(){
    for (int i=0;i<maxn;i++){
        E[i].clear();
        dist[i] = INF;
        inq[i] = 0;
    }
}
typedef pair<int, int> P ;

priority_queue<P, vector<P>, greater<P>> que;
void dijk(int& s){
    dist[s]=0;

    que.push(make_pair(0,s));
    while (!que.empty()){
        int w = que.top().first;
        int now = que.top().second;
        // cout << now << endl;
        que.pop();
        for (int i=0;i<E[now].size();i++){
            if (dist[now]+E[now][i].first < dist[E[now][i].second]){
                dist[E[now][i].second] = dist[now] + E[now][i].first;
                que.push(make_pair(dist[E[now][i].second], E[now][i].second));
            }
        }
    }
}

int main(){
    while (cin >> n >> m){
        init();
        // cout << n << m;
        int u, v, w;
        for (int i=0;i<m;i++){
            cin >> u>>v>>w;
            E[u].push_back( make_pair(w,v) );
            E[v].push_back( make_pair(w,u) );
        }
        int s, t;
        scanf("%d %d", &s, &t);

       dijk(s);
       if (dist[t] == INF) cout << -1 << endl;
       else cout << dist[t] << endl;
    }

}
