#include <iostream>
// #include <>
using namespace std;

const int N = 10;
int n,path[N];
bool vis[N];

void dfs(int u)
{
  if (u==n)
  {
    for (int i=0;i<n;i++) printf("%d ", path[i]);
    puts("");
    return;
  }

  for (int i=1;i<=n;i++)
  {
    if (!vis[i])
    {
      vis[i] = true;
      path[u]=i;
      dfs(u+1);
      vis[i] = false;
    }
  }
}

int main()
{
  cin >> n;
  dfs(0);
}
