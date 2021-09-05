//vis1=1;

// 0MS	1424K


#include <queue>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 103;
int n,m;
struct Edge{
    int f,t,w;
    Edge(){}
    Edge(int _f, int _t, int _w): f(_f), t(_t), w(_w) {}
    bool operator<(const Edge& b) const { return !(w<b.w); }
};
vector<Edge> G[maxn];
int vis[maxn];
void init(){
    for (int i=0;i<maxn;i++) {
        G[i].clear();
        vis[i] = 0;
    }
}
int prim(){
    priority_queue<Edge> heap;
    int ans = 0;
    vis[1]=1;
    for (int i=0; i<G[1].size();i++){
        heap.push(G[1][i]);
    }
    while (heap.size()){
        auto tmp = heap.top(); heap.pop();
        int now = tmp.t;
        if (vis[now]) continue;
        vis[now] = 1;
        ans += tmp.w;

        for (int i=0;i<G[now].size();i++){
            heap.push(G[now][i]);
        }
    }
    return ans;
}

int main(){
    while (scanf("%d%d", &m,&n)){
        if (m==0) break;
        init();
        for (int i=0;i<m;i++){
            int x,y,z;
            scanf("%d%d%d", &x,&y,&z);
            G[x].push_back(Edge(x, y,z));
            G[y].push_back(Edge(y, x,z));
        }
        int ans = prim();
        for (int i=1;i<=n;i++){
            if (vis[i]==0){
                ans = -1;
                break;
            }
        }
        if (ans == -1) cout << "?\n";
        else cout << ans << endl;
    }
}