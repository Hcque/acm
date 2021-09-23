
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 510, M = 2510*2+200;
int f, n,m1, m2;
int h[N], e[M], ne[M], w[M], idx;

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

int st[N], dist[N], cnt[N];
void spfa()
{
    queue<int> que;
    memset(dist, 0, sizeof dist);
    memset(st, 0, sizeof dist);
    memset(cnt, 0, sizeof dist);
    for (int i = 1; i <= n; i ++ )
    {
        que.push(i);
        st[i] = 1;
    }
    while (que.size())
    {
        // cout << que.size()<< " " ;
        auto t = que.front(); que.pop();
        st[t] = 0;
        
        for (int i = h[t]; ~i; i= ne[i])
        {
            int ver = e[i];
            if (dist[ver] > dist[t] + w[i]){
                dist[ver] = dist[t] + w[i];
                cnt[ver] = cnt[t] + 1;
                if (cnt[ver] >= n){
                    puts("YES");
                    return;
                }
                if (!st[ver])
                {
                    st[ver] = 1;
                    que.push(ver);
                }
            }
        }
    }
    puts("NO");

}

int main()
{
    cin >> f;

    while (f--)
    {
        scanf("%d%d%d", &n, &m1, &m2);

        memset(h,-1, sizeof h);
        idx = 0;
        while (m1--)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a,b,c), add(b,a,c);
        }

        while (m2--){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a,b,-c);
        }
        spfa();

    }
}