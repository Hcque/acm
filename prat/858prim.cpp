
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510, M = 1e5+10, INF = 0x3f3f3f3f;
int n,m;
int g[N][N];

int dist[N], st[N];
int prim()
{
    int ans = 0;
    memset(dist, 0x3f, sizeof dist);
    // st[1] = 1; dist[1] = 0;

    for (int v = 0; v < n; v ++ ){
        int t = -1;
        for (int i = 1; i <= n; i++){
            if (!st[i] &&  ( t == -1 || dist[t] > dist[i])){
                t = i;
            }
        }
        if (v && dist[t] == INF)  return -1;
        if (v) ans += dist[t];
        st[t] = 1;

        for (int i = 1; i <= n; i ++ ) dist[i] = min(dist[i], g[t][i]);
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    memset(g,INF, sizeof g);
    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(c, g[a][b]);
    }
    int ans = prim();
    for (int i = 1; i <= n; i ++ ){
        if (dist[i] > INF/2) {
            ans = -1; break;
        }
    }

    if (ans == -1) puts("impossible");
    else printf("%d\n", ans);
}