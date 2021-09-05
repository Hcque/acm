// https://acm.hdu.edu.cn/showproblem.php?pid=1863
// 0MS	1404K

#include <queue>
#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;
const int maxn = 103;
struct Edge{
    int to;
    ll w;
    Edge(int _t, ll _w): to(_t), w(_w){}
    Edge(){}
    bool operator<(const Edge& other) const{ return w > other.w; }
};
std::priority_queue<Edge> que;
std::vector<Edge> G[maxn];

int vis[maxn];
void init(){
    for (int i=0;i<maxn;i++) G[i].clear();
    while (que.size()) que.pop();
    memset(vis, 0, maxn*sizeof(int));
}
ll prim(){
    vis[1]=1;
    ll ans = 0;
    for (int i=0;i<G[1].size();i++)
        que.push(G[1][i]);
    while (!que.empty()){
        Edge e = que.top(); que.pop();
        if (vis[e.to]) continue;
        vis[e.to] = 1;
        ans += e.w;
        for (int i=0;i<G[e.to].size();i++){
            que.push(G[e.to][i]);
        }
    }
    return ans;
}

int main(){
    int N, M;
    while (scanf("%d %d", &N,&M) == 2){
        if (N==0) break;
        init();
        for (int i=0;i<N;i++){
            int u, v;
            ll  w;
            scanf("%d %d %d", &u,&v,&w);
            G[u].push_back( Edge(v, w) );
            G[v].push_back( Edge(u, w) );
        }
        ll res =  prim();
        for (int i=1;i<=M;i++) {
            if (vis[i]==0) 
                res = -1;
        }
        if (res==-1)
            printf("?\n");
        else
            printf("%d\n", res);
    }
}