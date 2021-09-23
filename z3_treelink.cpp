

const int maxn = 1e6+10;

int v[maxn];
int fa[maxn], dep[maxn], son[maxn], siz[maxn];

void dfs1(int u, int f){
    fa[u] = f;
    dep[u] = dep[f]+1;
    siz[u]=1;
    int maxsize = -1;
    for (int i=h[u];~i;i=ne[i]){
        int v = e[i];
        if (v==f) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if (siz[v] > maxsize){
            maxsize = siz[v];
            son[u] = v;
        }
    }
}

int tim,dfsn[maxn],top[maxn],w[maxn];

void dfs2(int u,int t){
    dfsn[u] = ++tim;
    top[u] = t;
    w[tim] = v[u];

    if (!son[u]) return;
    dfs2(son[u],t);
    for (int i=h[u];~i;i=ne[i]){
        int v = e[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}







