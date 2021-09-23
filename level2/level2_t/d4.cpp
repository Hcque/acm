

#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e5+10, M = 2*N;
int n;
int h[N], e[M], ne[M], idx;
int vis[N], ans=1e9;

void add(int a, int b)
{
    e[idx]=b, ne[idx]=h[a], h[a]=idx++;
}
int dfs(int u)
{
    vis[u] = 1;

    int siz = 1, res = 0;
    for (int i=h[u];~i;i=ne[i])
    {
        int v = e[i];
        if (!vis[v])
        {
            // vis[v] = 1;
            int s = dfs(v);
            siz += s;
            res = max(res, s);
        }
    }

    res = max(res, n-siz);
    ans = min(ans, res);
    return siz;
}

int main()
{
    cin >> n;

    memset(h,-1,sizeof(h));
    for (int i=0;i<n-1;i++)
    {
        int a, b;
        cin >> a>>b;
        add(a,b), add(b,a);
    }
    dfs(1);
    cout << ans << endl;
}