// 15MS	1456K
// queue
// 15MS	1456K

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 2e2+10;

struct Edge{
    int to, w;
    Edge(int _t, int _w):to(_t), w(_w){}
    Edge(){}
};
int s,t;
int n,m;
const int INF = 1e9;
vector<Edge> E[maxn];
int vis[maxn], dist[maxn];

void init(){
    for (int i=0;i<maxn;i++){
        E[i].clear();
    }
}
int spfa(int &s){
    fill(dist,dist+n,INF);
    fill(vis,vis+n,0);
    queue<int> que;
    dist[s]=0; vis[s]=1;
    que.push(s);
    while (que.size()){
        auto now = que.front();que.pop();
        vis[now]=0;
        for (int i=0;i<E[now].size();i++){
            int v = E[now][i].to;
            int w = E[now][i].w;

            if (dist[v] > dist[now]+w){
                dist[v] = dist[now]+w;
                if (!vis[v]){
                    vis[v]=1;
                    que.push(v);       
                }
            }
        }
    }
    if (dist[t]==INF) return -1;
    else return dist[t];
}
int main(){
    while (scanf("%d%d", &n,&m)!=EOF){
        init();
        for (int i=0;i<m;i++){
            int a,b,c;
            scanf("%d%d%d", &a,&b,&c);
            E[a].push_back(Edge(b,c));
            E[b].push_back(Edge(a,c));
        }
        scanf("%d%d",&s,&t);
        int ans = spfa(s);
        cout << ans << endl;
    }
}