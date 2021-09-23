// u,i

#include <iostream>
using namespace std;

const int N = 12;
int n, path[N], vis[N];
void dfs(int u)
{
    if (u==n+1) {
        for (int i=1;i<=n;i++) printf("%d ",path[i]);
        printf("\n");
        return;
    }
    for (int i=1;i<=n;i++){
        if (!vis[i])
        {
            vis[i] = 1;
            path[u] = i;
            dfs(u+1);
            vis[i] = 0;
        }
    }
}
int main()
{
    cin >> n;
    dfs(1);
}
