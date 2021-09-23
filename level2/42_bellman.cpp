//https://www.acwing.com/problem/content/description/855/

//# <= k 
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 510, M = 10010;
int n,m, k;
int dist[N], backup[N];

struct Edge
{
    int a, b ,w;
} edges[M];

int bellman()
{
    memset(dist,0x3f, sizeof dist);
    dist[1] = 0;

    for (int i=0;i<k;i++)
    {
        memcpy(backup, dist, sizeof dist);
        for (int j = 0;j<m;j++)
        {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w);
        }
    }
    return dist[n];
}

int main()
{
    scanf("%d%d%d", &n,&m,&k);
    for (int i=0;i<m;i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b,&w);
        edges[i] = {a,b,w};
    }

    int t = bellman();
    if (t > 0x3f3f3f3f/2) puts("impossible");
    else printf("%d\n", t);

}

