// memeset-1
// add b,a
// M = 2*N;


#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5+10, M = 2*N;
int n;
int h[N],e[M],ne[M],idx;
int vis[N], ans = 1e9;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int u)
{
    vis[u] = true;
    int sum = 1, res = 0;
    for (int i=h[u]; i!=-1;i=ne[i])
    {
        int v = e[i];
        if (!vis[v])
        {
            int s = dfs(v);
            sum += s;
            res = max(res,s);
        }
    }
    res = max(res,n-sum);
    ans = min(ans, res);
    return sum;
}

int main()
{
    cin >> n;
    memset(h,-1,sizeof(h));
    for (int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        add(a,b);
        add(b,a);
    }
    dfs(1);
    cout << ans << endl;
}