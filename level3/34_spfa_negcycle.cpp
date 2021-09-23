// xuni source
// dist renyi zhi

// #one trick :  >> 2*N

// https://www.acwing.com/problem/content/906/
// stack to -- fast

#include <cstring>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, M = 5210;

int n,m1,m2;
int h[N], e[M], w[M], ne[M], idx;

int dist[N];
int q[N], cnt[N];
bool vis[N];

void add(int a,int b,int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

bool spfa()
{
    int hh = 0, tt = 0;
    memset(dist, 0, sizeof dist);
    memset(vis, 0, sizeof dist);
    memset(cnt, 0, sizeof dist);

    for (int i=1;i<=n;i++)
    {
        q[tt ++ ] = i;
        vis[i] = 1;
    }

    while (hh != tt)
    {
        int t = q[ hh ++ ];
        if (hh == N) hh = 0;
        vis[t] = 0;
        for (int i = h[t]; ~i;i=ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]){
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if (cnt[j] >= n) return true;
                if (!vis[j])
                {
                    q[ tt ++ ] = j;
                    if (tt == N) tt = 0;
                    vis[j] = true;
                }

            }
        }
    }
    return false;

}
int main()
{
    int T ;
    cin >> T;
    while (T--)
    {
        cin >> n >> m1 >> m2;
        memset(h,-1,sizeof h);
        idx = 0;
        while (m1--)
        {
            int a,b,c;
            cin >> a >> b >> c;
            add(a,b,c), add(b,a,c);
        }

        while (m2--)
        {
            int a ,b,c;
            cin >> a>>b>>c;
            add(a,b,-c);
        }
        if (spfa()) puts("YES");
        else puts("NO");
    }
}

