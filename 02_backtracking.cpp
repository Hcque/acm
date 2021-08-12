#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 30
int N,M,T;
int sx,sy,fx,fy;
int vis[MAXN][MAXN];
int ma[MAXN][MAXN];
int ans = 0;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
void dfs(int x, int y){
    
    if (x==fx && y==fy) {
        ans++;
	return;
    }
    vis[x][y] = 1;
    for (int i=0;i<4;i++){
        int nx = dx[i]+x;
        int ny = dy[i]+y;
	if (nx<1 || nx>N || ny<1 || ny>N) continue;
	if (ma[nx][ny] != 2 && vis[nx][ny] != 1){
	    dfs(nx, ny);
	}
    }
    vis[x][y] = 0;
    return;
}

int main()
{

    cin >>N>>M>>T;
    cin>>sx>>sy>>fx>>fy;
    int tx, ty;
    memset(ma, 0, sizeof(ma));
    memset(vis, 0, sizeof(vis));
    for (int i=0;i<T;i++){
    	cin >> tx >> ty;
	ma[tx][ty] = 2;
    }
    dfs(sx,sy);
    cout << ans << endl;

    return 0;
}
