// https://www.luogu.com.cn/problem/P3384
// https://github.com/StableAgOH/Codebase/blob/master/Code/

#include <iostream>
using namespace std;
const int maxn= 1e5+5;
const int maxm= 2e5+5;

int n,m,r,mod,v[maxn];
struct E{
    int to, next;
    E(){}
    E(int _t, int _n): to(_t), next(_n){}
} Edge[maxn];
int tot, Head[maxn];
inline void addEdge(int u, int v){
    Edge[tot] = E(v, Head[u]);
    Head[u] = tot++;
    Edge[tot] = E(u, Head[v]);
    Head[v] = tot++;
}

int fa[maxn], dep[maxn], siz[maxn], son[maxn];
void dfs1(int u, int f){
    fa[u] = f;
    dep[u] = dep[f]+1;
    siz[u] = 1;
    int max_size = -1;
    for (int i=Head[u];~i;i=Edge[i].next){
        int v = Edge[i].to;
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (max_size < siz[v]){
            max_size = siz[v];
            son[u] = v;
        }
    }
}
int tim, dfsn[maxn], top[maxn], w[maxn];
void dfs2(int u, int t){
    dfsn[u] = ++tim;
    top[u] = t;
    w[tim] = v[u];
    if (!son[u]) 
        return;
    for (int i=Head[u];~i;i=Edge[i].next){
        int v = Edge[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}


// line tree
struct Node{
    int l,r,f,val;
} sgt[maxn*4];
inline int ls(int k){ return k<<1; }
inline int rs(int k){ return k<<1|1; }
void pushup(int k){
    sgt[k].val = (sgt[ls(k)].val+sgt[rs(k)].val)%mod;
}
void pushdown(int k){
    sgt[ls(k)].f += sgt[k].f;
    sgt[rs(k)].f += sgt[k].f;
    sgt[ls(k)].val += (sgt[k].r-sgt[k].l+1)*sgt[k].f;
    sgt[rs(k)].val += (sgt[k].r-sgt[k].l+1)*sgt[k].f;
    sgt[k].f = 0;
}
void build(int l, int r, int k=1){
    sgt[k].l = l; sgt[k].r = r; 
    if (l==r) {
        sgt[k].val = w[l]%mod;
        return;
    }
    int m = (l+r)>>1;
    build(l,m,ls(k));
    build(m+1,r,rs(k));
    pushup(k);
}

void modify(int x, int y, int z, int k=1){
    int l = sgt[k].l; int r = sgt[k].r;
    if (x<=l && r<=y){
        sgt[k].f += z;
        sgt[k].val += (r-l+1)*z;
        sgt[k].val %= mod;
        return;
    }
    int m = (l+r)>>1;
    if (x<=m) modify(x, y, z, ls(k));
    if (y>m) modify(x, y, z, rs(k));
    pushup(k);
}

int query(int x, int y,int k=1){
    int l = sgt[k].l; int r = sgt[k].r;
    if (x<=l && r<=y){
        return sgt[k].val;
    }
    if (sgt[k].f) pushdown(k);
    int m = (l+r)>>1; int ans = 0;
    if (x<=m) ans += query(x, y, ls(k));
    if (y>m) ans += query(x, y,rs(k));
    return ans % mod;
}

void mchain(int x, int y ,int z){
    z%=mod;
    while (top[x]!=top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x,y);
        modify(dfsn[top[x]], dfsn[y], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x,y);
    modify(dfsn[x],dfsn[y], z);
}

int qchain(int x, int y){
    int ret=0;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);

        ret += query(dfsn[top[x]], dfsn[x]);
        x = fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x, y);
    ret += query(dfsn[x], dfsn[y]);
    return ret % mod;
}

inline void mson(int x, int z){
    modify(dfsn[x], dfsn[x]+siz[x]-1, z);
}
 int qson(int x){
    return query(dfsn[x], dfsn[x]+siz[x]-1);
}

int main(){
    scanf("%d%d%d%d", &n, &m, &r, &mod);
    for (int i=1;i<=n;i++){
        scanf("%d", &v[i]);
    }
    for (int i=1;i<n;i++){
        int u, v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    dfs1(r,r);
    dfs2(r,r);
    build(1,n);
    while (m--){
        int op,x,y,z;
        scanf("%d", &op);
        switch (op){
            case 1: scanf("%d%d%d", &x,&y,&z);
            mchain(x,y,z); break;
            case 2: scanf("%d%d", &x,&y);
            cout << qchain(x,y) << endl; break;
            case 3: scanf("%d%d%d", &x,&y);
            mson(x,y); break;
            case 4: scanf("%d%d", &x);
            cout << qson(x) << endl; break;
        }
    }

    

}