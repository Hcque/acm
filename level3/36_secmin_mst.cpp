
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 100010, M = 300010;


int n, m;
int h[N], e[M], ne[M], idx;
struct Edge{
    int a, b, w, used;
    bool operator<(const Edge& t) const{
        return w < t.w;
    }
} edges[M];
int fa[N];
int depth[N],  fa[N][17], d1[N][17], d2[N][17];
int q[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int Find(int x)
{
    if (fa[x] != x) return x;
    return fa[x] = Find(fa[x]);
}

LL kruskal()
{
    for (int i = 1; i <= n; i ++ ) fa[i] = i;
    sort(edges, edges + m);
    LL ans = 0;
    for (int i = 0;i < m;i++ )
    {
        int a = Find(edges[i].a), b = Find(edges[i].b), w = edges[i].w;
        if (a != b){
            fa[a] = b;
            ans += w;
             edges[i].used = 1; 
        }
    }
}

void build()
{
    memset(h,-1,sizeof h);
    for (int i = 0; i < m; i ++ ){
        if (edges[i].used)
        {
            int a = edges[i].a, b = edges[i].b, w = edges[i].w;
            add(a, b, w), add(b, a, w);
        }
    }
}

void bfs()
{
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    while (hh <= tt)
    {
        int  t = q[hh ++ ];
        for (int i = h[t]; ~i; i= ne[i])
        {
            int j = e[i];
            if (depth[j] > depth[t] + 1){
                depth[j] = depth[t] + 1;
                q[ ++ tt] = j;
                fa[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = -INF;
                for (int k = 1; k<= 16; k ++ )
                {
                    int anc 
                }
            }
        }
    }
}

int lca(int a, int b, int w)
{
    static 
}


int main()
{
    scanf("%d%d", &n, &m);
    LL sum = kruskal();
    build();
    bfs();

    LL ans = 1e18;
    for (int i = 0;i<m;i ++ ) 
    {
        if (!edges[io].used){
            int a - edges[i].a, b = edges[i].b,  w=edges[i].w;
            ans = min(ans, sum + lca(a, b, w) );
        }
    }
    printf("%lld\n", ans);
}

