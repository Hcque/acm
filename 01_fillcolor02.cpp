#include <iostream>
using namespace std;

int N;
#define MAXN 35
int M[MAXN][MAXN];
int ans[MAXN][MAXN];

int vis[MAXN][MAXN];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

void find_1(int x, int y){
    vis[x][y] = 1;
    ans[x][y] = 0;
     for (int k=0;k<4;k++){
	    int newx = dx[k] + x; 
	    int newy = dy[k] + y; 
	    if (  ans[newx][newy] != 1 && vis[newx][newy] == 0 &&
            newx >= 0 && newx <= N &&
            newy >= 0 && newy <= N 
            ){
            find_1(newx, newy);
	    }
	}
}

int main()
{
    cin >> N;
    for (int i=1;i<=N;i++){
        for (int j=1;j<=N;j++){
            cin >> M[i][j];
            if (M[i][j] != 1) 
                ans[i][j] = 2;
            else 
                ans[i][j] = 1;
            vis[i][j] = 0;
        }
    }
    find_1(0,0);
    for (int i=1;i<=N;i++){
        for (int j=1;j<=N;j++){
            if (j != N)
                cout << ans[i][j] << ' ';
            else cout << ans[i][j];
        }
        if (i != N)cout << "\n";
    }

    return 0;
}
