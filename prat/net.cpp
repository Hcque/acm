#include <cstring>
#include <iostream>
using namespace std;

const int N = 1010, M = 20010, INF = 1e9;
int n,m,S,T;
int h[N], e[M], w[M], ne[M], idx;
int q[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int pre[N], vis[N], d[N];
int bfs()
{
   int hh = 0, tt = 0;
   memset(vis,0,sizeof vis);
   q[0] = S; vis[S] = 1; d[S] = INF;
   while (hh <= tt )
   {
       int t = q[ hh ++ ];
       for (int i = h[t];~i;i=ne[i])
       {
           int j = e[i];
           if (!vis[j] && w[i] > 0 ) {
               d[j] = min(d[t], w[i]);
               vis[j] = 1;
               pre[j] = i;
               if (j == T) return 1;
               q[ ++ tt ] = j;
           }
       }
   }
   return 0;
}

int EK()
{
    int ans = 0;
    while (bfs())
    {
        ans += d[T];
        for (int i = T;i != S; i= e[pre[i]^1])
            w[pre[i]] -= d[T], w[pre[i]^1] += d[T] ;
    }
    return ans;

}

int main()
{
    cin >> n >> m>> S >> T;
    memset(h,-1,sizeof h);
    for (int i = 0; i < m; i ++ )
    {
        int u,v,c;
        scanf("%d%d%d", &u, &v, &c);
        add(u,v,c), add(v,u,0);
    }
    printf("%d\n", EK());
    
}