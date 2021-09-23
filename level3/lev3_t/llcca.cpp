#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

const int N = 40010, M = N;
const int LOG = 15;
int n, m;
int h[N], e[M], ne[M], idx;
int root;
int fa[N][LOG+1], depth[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int & u, int dep)
{
    depth[u] = dep;
    // cout << dep << endl;
    for (int i=h[u]; ~i; i=ne[i]){
        int j = e[i];
        fa[j][0] = u;
        // cout << u << endl;
        for (int k=1;k<=LOG;k++ ){
            fa[j][k] = fa[ fa[j][k-1] ][k-1];
        }
        dfs(j, dep+1);
    }
}

int lca(int x, int y)
{
    if (depth[x] < depth[y]) swap(x, y);
    for (int k = LOG; k >=0 ; k--){
        if (depth[fa[x][k]] >= depth[y]){
            x = fa[x][k];
        }
    }
    if (x == y) return x;
    assert(depth[x] == depth[y]);
    for (int k = LOG; k >= 0; k-- )
    {
        if (fa[x][k] != fa[y][x]){
            x = fa[x][k];
            y = fa[y][k];
         }
    }
    return fa[x][0];
}

int main()
{
    cin >> n;
    memset(h,-1,sizeof h);
    for (int i=0;i<n;i++ ){
        int from, to;
        cin >> from >> to;
        if (to == -1) root = from;
        else add(to, from);
    }
    // cout << root << endl;
    dfs(root, 1);
    depth[0] = 0; // safety

    // for (int j = 0; j <= n; j ++ )
        // for (int i = 0; i <= LOG; i ++ )
            // cout << fa[j][i] << " ";
        // cout << "\n";

    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p==b) puts("2");
        else puts("0");
    }
}