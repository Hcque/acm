
#include <iostream>
using namespace std;

const int N = 20;
int n;
char g[N][N];
bool col[N], dg[N], udg[N];

void dfs(int x)
{
    if (x==n){
        for (int i=0;i<n;i++) puts(g[i]);
        puts("");
        return;
    }

    for (int y=0;y<n;y++)
    {
        if ( !col[y] && !dg[x+y] && !udg[n+x-y])
        {
            col[y] = dg[x+y] = udg[n+x-y] = true;
            g[x][y] = 'Q';
            dfs(x+1);
            col[y] = dg[x+y] = udg[n+x-y] = false;
            g[x][y] = '.';
        }
    }


}

int main()
{
    cin >> n;
    for (int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            g[i][j] = '.';
    dfs(0);
}