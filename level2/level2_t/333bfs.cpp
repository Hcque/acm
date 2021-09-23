#include <iostream>
#include <cstring>


using namespace std;
const int N = 110;
int n, m;
int g[N][N], d[N][N];
struct Point
{
    int x, y;
};
Point q[N*N];

int bfs()
{
    int hh = 0, tt = 0;
    q[0] = {0,0};
    memset(d, -1, sizeof df);
    d[0][0] = 0;

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    while (hh <= tt)
    {
        auto t = q[hh ++ ];
        for (int i = 0;i < 4; i ++ )
        {
            int nx = t.x + dx[i], ny = t.y + dy[i] ;
            if (0 <= nx && nx < n && 0 <= ny && ny < m 
            && d[nx][ny] == -1 && g[nx][ny] == 0)
            {
                q[ ++ tt ] = {nx, ny};
                d[nx][ny] = d[x][y] + 1;
            }
        }
    }
    return d[n-1][m-1];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <m; j ++ )
        {
            cin >> g[i][j];
        }
    }
    printf("%d\n", bfs());
}