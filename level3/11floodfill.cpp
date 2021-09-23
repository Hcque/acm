// https://www.acwing.com/problem/content/1099/


#include <iostream>

using namespace std;
const int N = 1010;
int n,m;
char g[N][N];
int vis[N][N];

struct Point{
    int x, y;
};
Point q[N*N];

int dx[8] = {0,0,1,-1,-1,1,1,-1 };
int dy[8] = {1,-1,0,0,-1,1,-1, 1};

void flood(Point p){
    int hh= 0, tt = 0;
    q[0] = p;
    vis[p.x][p.y] = 1;
    while (hh <= tt)
    {
        auto t = q[ hh ++ ];
        for (int i = 0; i < 8; i ++ )
        {
            int nx = t.x + dx[i], ny = t.y + dy[i];
            if ( 0 <= nx && nx < n && 0 <= ny && ny < m
            && g[nx][ny] == 'W' && vis[nx][ny] == 0)
            {
                q[ ++ tt ] = {nx, ny};
                vis[nx][ny] = 1;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++ )
    {
        scanf("%s", &g[i]);
    }
    int ans = 0;
    for (int i=0;i<n;i++ ){
        for (int j = 0; j < m; j ++){
            if (vis[i][j] == 0 && g[i][j] == 'W'){
                flood({i,j});
                ans ++;
            }
        }
    }
    printf("%d\n", ans);
}