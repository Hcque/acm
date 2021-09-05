#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge{
    int to, w;
    Edge() {}
    Edge(int _t, int _w): to(_t), w(_w) {}
    bool operator<(const Edge& b) const { return w> b.w; }
};
const int maxn = 104;
vector<Edge> E[maxn];
int vis[maxn], n, m;
priority_queue<Edge> heap;
void init(){
    for (int i=0;i<maxn;i++) {
        E[i].clear();
        vis[i] = 0;
    }
    while (heap.size()) heap.pop();
}
int prim(){
    vis[1] = 1;
    for (int i=0;i<E[1].size();i++){
        heap.push(E[1][i]);
    }
    int ans = 0;
    while (heap.size()){
        auto tmp = heap.top(); heap.pop();
        int now = tmp.to; int w = tmp.w;
        if (vis[now]) continue;
        vis[now] = 1;
        ans += w;

        for (int i=0;i<E[now].size();i++){
            heap.push(E[now][i]);
        }
    }
    return ans;
}

int main(){
    while (scanf("%d%d", &m,&n)){
        if (m==0) break;
        init();

        while (m--){
            int x, y,z;
            scanf("%d%d%d", &x,&y,&z);
            E[x].push_back(Edge(y,z));
            E[y].push_back(Edge(x,z));
        }
        int res = prim();
        for (int i=1;i<=n;i++){
            if (!vis[i]) {
                res = -1; break;
            }
        }
        if (res == -1) cout << "?\n";
        else cout << res << endl;
    }
}


