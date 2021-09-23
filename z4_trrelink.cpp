const int maxn = 1e6, maxm = 1e6;

int h[maxn], e[maxm], ne[maxm];
int v[maxn];

int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs1(int u, int f){
    fa[u]=f;
    dep[u]=dep[f]+1;
    siz[u]=1;
    int maxsize = -1;
    for (int i=h[i];~i;i=ne[i]){
        int v=e[i];
        if (v = fa[u]) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if (siz[v]>maxsize){
            maxsize = siz[v];
            son[u] = v;
        }
    }
}

int tim, dfsn[maxn],top[maxn],w[maxn];
int dfs2(int u, int t){
    dfsn[u]==++tim;
    top[u] = t;
    w[tim] = v[u]; 
    if (!son[u]) return;
    
    for (int i=h[u];~i;i=ne[i]){
        int v=e[i];
        if (fa[u]==v || v==son[u]) continue;
        dfs2(v,v);
    }
}



// lineTree



