// build nw r;push up
// 1,n,w
// push up;
// l,r <<1?
// LL

#include <iostream>
#include <cstring>

using namespace std;
const int N = 1e5+10, M = 2*N;

typedef long long LL;
int n,m;
int h[N], e[M], w[M], ne[M], idx;
int fa[N], sz[N], dep[N], son[N];
int dfsn[N], nw[N], top[N], cnt;

struct Node{
    int l, r;
    LL add, sum;
} tr[N*4];
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}


void dfs1(int u, int father, int depth)
{
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u];~i;i=ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth+1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}
void dfs2(int u, int t)
{
    dfsn[u] = ++ cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}
void pushup(int u)
{
    tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}

void pushdown(int u)
{
    if (tr[u].add){
        Node &root = tr[u], &left = tr[u<<1], &right = tr[u<<1|1];
        left.add += root.add;
        right.add += root.add;
        left.sum += (left.r-left.l+1)*root.add;
        right.sum += (right.r-right.l+1)*root.add;
        root.add =0;
    }
}
void build(int u, int l, int r)
{
    tr[u] = {l,r, 0, nw[r]};
    if (l == r) return;
    int mid = l+r>>1;
    build(u<<1,l,mid), build(u<<1|1,mid+1, r);
    pushup(u);
}


void update(int u, int l, int r, int k)
{
    if (l <= tr[u].l && tr[u].r <= r) 
    {
        tr[u].add += k;
        tr[u].sum += (tr[u].r-tr[u].l+1)*k;
        return;
    }
    pushdown(u);
    int mid = tr[u].l+tr[u].r>>1;
    if (l <= mid) update(u<<1, l, r, k);
    if (r > mid) update(u<<1|1, l,r, k);
    pushup(u);
}
LL query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL ans = 0;
    if (l <= mid) ans += query(u<<1,l,r);
    if (r > mid) ans += query(u<<1|1, l,r);
    return ans;
}

void update_tree(int u, int k)
{
    update(1, dfsn[u], dfsn[u]+sz[u]-1, k);
}
LL query_tree(int u)
{
    return query(1, dfsn[u], dfsn[u]+sz[u]-1);

}
void update_range(int u, int v, int k)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u,v);
        update(1, dfsn[top[u]], dfsn[u], k);
        u = fa[top[u]];
    }

    if (dep[u] < dep[v]) swap(u, v);
    update(1, dfsn[v], dfsn[u], k);
}
LL query_range(int u, int v)
{
    LL ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ans += query(1, dfsn[top[u]], dfsn[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ans += query(1, dfsn[v], dfsn[u]);
    return ans;
}

int main()
{
    scanf("%d",&n);
    for (int i = 1;i<=n;i++) scanf("%d", &w[i]);

    memset(h, -1, sizeof h);

    for (int i = 0; i<n-1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b,a);
    }
    dfs1(1,-1,0);
    dfs2(1,1);
    build(1,1,n);

    scanf("%d", &m);
    while (m--)
    {
        int t,u,v,k;
        scanf("%d%d",&t,&u);
        if (t == 1)
        {
            scanf("%d%d", &v,&k);
            update_range(u,v,k);
        }
        else if (t == 2)
        {
            scanf("%d", &k);
            update_tree(u,k);
        }
        else if (t == 3){
            scanf("%d", &v);
            printf("%lld\n", query_range(u, v));
        }
        else printf("%lld\n", query_tree(u));
    }

}

