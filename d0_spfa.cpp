// https://acm.hdu.edu.cn/showproblem.php?pid=1874
// spfa
// 31MS	1464K

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

queue<int> que;
void spfa(int& s){
    dist[s]=0;
    que.push(s); inq[s]=1;
    while (!que.empty()){
        int now = que.front(); que.pop();
        for (int i=0;i<E[now].size();i++){
            if (dist[now]+E[now][i].first < dist[E[now][i].second]){
                dist[E[now][i].second] = dist[now] + E[now][i].first;
                que.push(E[now][i].second);
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

       spfa(s);
       if (dist[t] == INF) cout << -1 << endl;
       else cout << dist[t] << endl;
    }

}
