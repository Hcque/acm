#include <iostream>
#include <cstring>
using namespace std;

const int N = 110;
int n, g[N][N];
int dist[N], vis[N];

int prim()
{
    int ans = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for (int i = 0; i < n; i ++ ){
        int t = -1;
        for (int j = 1; j <= n; j ++ ){
            if (!vis[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }
        ans += dist[t];
        vis[t] = 1;
        for (int j = 1; j <= n; j++ ) dist[j] = min(dist[j], g[t][j]);
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i=1;i<=n;i++){
        for (int j = 1; j <= n; j++){
            cin >> g[i][j];
        }
    }
    printf("%d\n", prim());

}