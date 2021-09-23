// https://www.acwing.com/problem/content/1142/

// 1140. 最短网络

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = N*N;
int n, m;
int g[N][N];

// prim

int dist[N];
int q[N], vis[N];

// int prim()
// {
//     int ans = 0;
//     int hh = 0, tt = 0;
//     memset(dist, 0x3f, sizeof dist);
//     q[0] = 1;   
//     dist[1] = 0;
//     while (hh <= tt)
//     {
//         int now = q[ hh ++ ];
//         int distance = 1e9;int min_nxt;
//         for (int i=0;i<n;i++)
//         {
//             int nxt = i+1; 
//             if (nxt == now) continue;
//             if (dist[nxt] < distance) {
//                 distance = dist[nxt];
//                 min_nxt = nxt;
//             }
//         }
//         q[ tt ++ ] = min_nxt;
//         ans += distance;
//         for (int i=0;i<n;i ++ )
//         {
//             int nxt = i+1;
//             dist[nxt] = min(dist[nxt], g[min_nxt][i]);
//         }
//     }
// }

int prim()
{
    int ans = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for (int i=0; i<n; i++ )
    {
        int t = -1;
        for (int j = 1; j <= n; j++ )
            if (!vis[j] && t == -1 || dist[t] > dist[j])
                t = j;
        ans += dist[t];
        vis[t] = 1;

        for (int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], g[t][j]);
    } 
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i= 1;i <= n; i++ ){
        for (int j =1; j <= n ; j ++ ){
            scanf("%d",&g[i][j]);
        }
    }
    printf("%d\n", prim());
}


// int fa[N];

// struct Edge
// {
//     int u,v,w;
//     bool operator<(const Edge& b) const { return w < b.w; }
// };

// Edge edges[M];

// int Find(int x)
// {
//     if (fa[x] == x) return x;
//     return fa[x] = Find(fa[x]);
// }

// bool Same(int x, int y)
// {
//     return Find(x) == Find(y);
// }
// void Union(int x, int y)
// {
//     int u = Find(x);
//     int v = Find(y);
//     if (u == v) return;
//     fa[u] = v;
// }

// int kruskal()
// {
//     int ans = 0;
//     for (int i=1;i<=n;i++) fa[i] = i;
//     sort(edges, edges+m);
//     for (int i=0;i<m;i++){
//         auto e = edges[i];
//         if (Same(e.u, e.v)) continue;
//         Union(e.u, e.v);
//         ans += e.w;
//     }
//     return ans;
// }
// int main()
// {
//     scanf("%d", &n);
//     m = 0;
//     for (int i=0;i<n;i++){
//         for (int j =0;j<n;j++ ){
//             scanf("%d", &g[i][j]);
//             if (i>=j) continue;
//             edges[m++] = {i+1,j+1, g[i][j]};
//         }
//     }

//     printf("%d\n",kruskal());        
// };