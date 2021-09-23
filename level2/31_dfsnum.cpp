
// https://www.acwing.com/problem/content/844/


#include <iostream>
using namespace std;
const int N = 10;
int n, path[N], vis[N];

void dfs(int u)
{
    if (u==n)
    {
        for (int i=0;i<n;i++) printf("%d ", path[i]);
        cout << endl;
        return;
    }
    for (int i=1;i<=n;i ++ )
        if (!vis[i])
        {
            path[u] = i;
            vis[i] = 1;
            dfs(u+1);
            vis[i] = 0;
        }
}

int main()
{
    cin >> n;
    dfs(0);
    return 0;
}