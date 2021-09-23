#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


const int N = 1e6+10, M = N;
int n,m;
int h[N], e[M], ne[M], w[M], idx;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

typedef pair<int,int> PII;
int dist[N], vis[N]; 
void dijk()
{
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    memset(dist, 0x3f,sizeof dist);
    memset(vis, 0, sizeof vis);

    heap.push({0, 1});dist[1] = 0;
    // vis[1] = 1;
    while (heap.size())
    {
        auto t = heap.top(); heap.pop();
        int now = t.second, distance = t.first;
        vis[now] = 0;

        for (int i = h[now];~i;i=ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[now] + w[i]){
                dist[j] = dist[now] + w[i];
                if (!vis[now]){
                    heap.push({dist[j], j});
                    vis[now] = 1;

                }
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) puts("-1");
    else printf("%d\n", dist[n]);
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    dijk();
}