// https://www.acwing.com/problem/content/1143/


#include <iostream>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 110, M = 210;
int n,m;
struct Edge{
    int u, v, w;
    bool operator<(const Edge& b) const { return w < b.w; }
} edges[M];

int fa[N];
int Find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

int Same(int x, int y)
{
    return Find(x) == Find(y);
}

void Union(int x, int y)
{
    int a = Find(x), b = Find(y);
    if (a==b) return;
    fa[a] = b;
}


int kruskal()
{
    int ans = 0;
    for (int i=1;i<=n;i++) fa[i] = i;
    sort(edges, edges+m);
    for (int i=0;i<m;i++){
        auto e = edges[i];
        if (Same(e.u, e.v)) continue;
        Union(e.u, e.v);
        ans += e.w;
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    int a,b,c;
    int all_w = 0;
    for (int i=0;i<m;i++ ){
        cin >> a>> b >> c;
        edges[i] = {a,b,c};
        all_w += c;
    } 

    int min_w = kruskal();
    printf("%d\n", all_w - min_w);

}