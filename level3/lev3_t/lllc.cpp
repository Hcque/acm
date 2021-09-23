#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 40010, M= N;
const int LOG = 16;
int n,m;
int fa[N][LOG], depth[N];

int h[N], e[M], ne[M], idx;
void add(int a,int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++ ;
}

void dfs(int &u, int dep)
{
    depth[u] = dep;

    for (int i=h[u];~i;i=ne[i])
    {
        int j = e[i];
        fa[j][0] = u;
        for (int k= 1; k <= 15; k++ )
            fa[j][k] = fa[ fa[j][k-1] ][k-1];
        dfs(j, dep+1);
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k -- )
    {
        if (depth[fa[a][k]] >= depth[b] )
            a = fa[a][k];
    }
    if (a == b) return a;
    for (int k = 15; k >= 0; k -- )
    {
        if (fa[a][k] != fa[b][k]){
            a = fa[a][k];
            b = fa[b][k];
        }
    }
    return fa[a][0];

}

int main()
{
    cin >> n;
    int root;
    memset(h,-1,sizeof h);
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if (b == -1) root = a;
        else add(b,a);
    }
    depth[0] = 0;

    dfs(root, 1);

    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a>>b;
        int p = lca(a, b);
        if (p == a) puts("1");
        else if (p== b) puts("2");
        else puts("0");
    }
}