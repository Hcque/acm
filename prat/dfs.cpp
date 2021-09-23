// https://www.acwing.com/problem/content/845/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 10;
int n;
char g[N][N];
int row[N], col[N], dia[N], mdig[N];
int cnt;
void output()
{
    for (int i = 0; i < n; i ++ ){
            puts(g[i]);
    }
    puts("");
}
void dfs(int x, int y, int c)
{
    //
    if (y >= n) x+=1, y = 0;
    if (x >= n) {
       if (c == n) output(); 
       return;
    }
    dfs(x,y+1, c);
    if (!row[x] && !col[y] && !dia[x+y] && !mdig[n+ x-y]){
        row[x] = col[y] = dia[x+y] = mdig[n+ x-y] = 1;
        g[x][y] = 'Q';
        dfs(x, y+1, c+1);
        g[x][y] = '.';
        row[x] = col[y] = dia[x+y] = mdig[n+ x-y] = 0;
    }

}
int main()
{
    cin >> n;
    for (int i =0; i < n; i ++) 
        for (int j = 0; j <n; j ++ ) 
            g[i][j] = '.';
    dfs(0,0, 0);

}