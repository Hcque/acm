#include <iostream>
#include <cstring>
#include <queue>
using namespace std;


const int N = 1010, M = 20010, INF = 1e9;
int n,m, S, T;
int h[N], e[M], w[M], ne[M], idx;
void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

int d[N], vis[N], pre[N];
int bfs()
{
    queue<int> que;
    que.push(S);
    memset(vis,0, sizeof vis);
    // memset(d,0, sizeof vis);
    d[S] = INF, vis[S] = 1;
    while (que.size())
    {
        auto t = que.front(); que.pop();
        for (int i = h[t]; ~i; i= ne[i])
        {
            int j = e[i];
            if (w[i]>0 && !vis[j])
            {
                vis[j] = 1;
                d[j] = min(d[t], w[i]);
                pre[j] = i;
                if (j == T) return 1;
                que.push(j);
            }
        }
    }
    return 0;
}

int EK()
{
    int ans = 0;
    while(bfs())
    {
        ans += d[T];
        for (int u = T; u != S; u = e[pre[u]^1 ])
            w[ pre[u]] -= d[T], w[pre[u]^1] += d[T];
    }
    return ans;
}
int main()
{
    cin >> n>>m>>S>>T;
    memset(h,-1, sizeof h);
    while (m--)
    {
        int a,b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);add(b,a,0);
    }
    printf("%d\n", EK());
}