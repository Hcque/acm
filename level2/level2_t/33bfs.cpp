

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;
typedef pair<int, int> PII;

int n,m;
int g[N][N];
int d[N][N];
PII q[N*N];

int dx[4]= {-1,1,0,0};
int dy[4]= {0,0,1,-1};

int bfs()
{
    memset(d, -1, sizeof d);
    d[1][1] = 0;
    int hh = 0, tt = 0;
    q[0] = {1,1};

    while (hh <= tt)
    {
        auto t = q[ hh ++];
        int x = t.first, y = t.second;
        for (int i = 0; i < 4; i ++ )
        {
            int nx = x+dx[i], ny = y + dy[i];
            if (1<= nx && nx<=n && 1<=ny && ny<=m && d[nx][ny]==-1 & g[nx][ny]!=1)
            {
                q[ ++ tt ] = {nx, ny};
                d[nx][ny] = d[x][y] + 1;
                // cout << nx << "|" << ny << d[nx][ny] << endl;
            }
        }
    }
    return d[n][m];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++ ){
        for (int j = 1; j <= m; j ++ ){
            scanf("%d", &g[i][j]);
        }
    }
    printf("%d\n", bfs());
}