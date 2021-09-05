// Union

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 104;

struct Edge{
    int from, to, w;
    Edge(){}
    Edge(int _f,int _t,int _w):from(_f),to(_t),w(_w){}
};
// vector<Edge> E[maxn];
vector<Edge> E;

int m, n, fa[maxn];
int Find(int x){
    if (x==fa[x]) return x;
    return fa[x] = Find(fa[x]);
}

int Same(int x, int y){
    return Find(x) == Find(y);
}

void Union(int x, int y){
    int u = Find(x); int v = Find(y);
    if (u==v) return;
    fa[u] = v;
}

bool cmp(Edge &a, Edge& b){
    return a.w < b.w;
}

void init(){
    for (int i=1;i<=n;i++) fa[i] = i;
    E.clear();
}
void kruskal(){
    int ans = 0;
    sort(E.begin(), E.end(), cmp);
    for (int i=0;i<E.size();i++){
        if (Same(E[i].from,E[i].to)) continue;
        Union(E[i].from, E[i].to);
        ans += E[i].w;
    }
    int con=1;
    for (int i=1;i<=n;i++){
        if (!Same(1,i)) {
            con = 0; break;
        }
    }
    if (con)
        cout << ans << endl;
    else cout << "?\n";
}
int main(){
    while (scanf("%d%d", &m,&n) == 2){
        if (m==0) break;
        init();

        while (m--){
            int a,b,c;
            scanf("%d%d%d", &a,&b,&c);
            E.push_back(Edge(a, b,c));
        }
        kruskal();
        
    }
}