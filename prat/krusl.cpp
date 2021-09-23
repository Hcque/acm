#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5+10, M = 2*1e5 + 10;
int n,m;
struct Edge{
    int u,v,w;
    bool operator<(const Edge& b) const { return w < b.w; }
} e[M];

int fa[N];
int Find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}


int kruskal()
{
    int ans = 0;
    for (int i = 1; i <= n;i ++ ) fa[i] = i;
    sort(e,e+m);
    for (int i = 0; i < m; i ++ )
    {
        int a = Find(e[i].u), b = Find(e[i].v);
        if (a != b){
        fa[a] = b;
        ans += e[i].w;
        }
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i ++ )
    {
        cin >>  e[i].u >> e[i].v >> e[i].w;
    }

    int ans = kruskal();    

    for (int i = 1; i <= n; i ++ ) {
        if(Find(i) != Find(1)) ans = -1;
    }
    if (ans == -1) puts("impossible");
    else printf("%d\n", ans);

}