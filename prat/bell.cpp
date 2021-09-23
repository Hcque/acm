#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510, M = 1e5+10;
int n, m, k;

struct Edge{
    int a, b, c;
} e[M];
int dist[N], backup[N];
void bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    memset(backup, 0x3f, sizeof dist);
    for (int i = 0; i < k; i ++ ){
        for (int j = 0; j < m; j ++ ){

            int a = e[j].a, b = e[j].b, c = e[j].c;
            dist[b] = min(dist[b], backup[a] + c);
        }
        memcpy(backup, dist, sizeof(dist));
    }
    if (dist[n] > 0x3f3f3f3f / 2) puts("impossible");
    else printf("%d\n", dist[n]);
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m ; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        e[i] = {a, b, c};
    }
    bellman_ford();
}

