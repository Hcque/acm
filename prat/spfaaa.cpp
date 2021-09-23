#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 2e3+10, M = 1e5+10;
int n,m, K;

int h[N], e[M], w[M], ne[M], idx;
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dist[N], st[N], cnt[N];
void spfa()
{
    queue<int> que;
    for (int i = 1; i <= n; i ++ ){
        que.push(i);
        st[i] = 1;
    }
    while (que.size())
    {
        auto t = que.front(); que.pop();
        st[t] = 0;
        for (int i = h[t]; ~i; i= ne[i])
        {
            int ver = e[i];
            if (dist[ver] > dist[t] + w[i]){
                dist[ver] = dist[t] + w[i];
                cnt[ver] = cnt[t] + 1;
                if (cnt[ver] > n) {
                    puts("Yes");
                    return;
                }
                if (!st[ver]){
                    que.push(ver);
                    st[ver] = 1;
                }
            }
        }
    }
    puts("No");

}

int main()
{
    cin >> n >> m ;
    memset(h,-1, sizeof h);
    for (int i = 0; i < m; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }    
    spfa();
    // if (dist[n] > 0x3f3f3f3f / 2) puts("impossible");
    // else printf("%d\n", dist[n]);
}