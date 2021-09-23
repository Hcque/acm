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

queue<int> que;
int dist[N], vis[N]; 
void spfa()
{
    
    memset(dist, 0x3f,sizeof dist);
    memset(vis, 0, sizeof vis);

    que.push(1);
    dist[1] = 0;
    while (que.size())
    {
        auto now = que.front(); que.pop();
        vis[now] = 0;

        for (int i = h[now];~i;i=ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[now] + w[i]){
                dist[j] = dist[now] + w[i];
                if (!vis[j]){
                    que.push(j);
                    vis[j] = 1;
                }
                
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) puts("impossible");
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

    spfa();
}
