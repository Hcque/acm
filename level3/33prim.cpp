// https://www.acwing.com/problem/content/1142/

// 1140. 最短网络

// cation param

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


int prim()
{
    int ans = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for (int i=0; i<n; i++ )
    {
        int t = -1;
        for (int j = 1; j <= n; j++ )
            if (!vis[j] && (t == -1 || dist[t] > dist[j]) )
                t = j;
        ans += dist[t];
        vis[t] = 1;
        cout << t << endl;

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
