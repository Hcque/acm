// https://acm.hdu.edu.cn/showproblem.php?pid=1863
// kruskal
// 31MS	1388K

#include <iostream>
#include <algorithm>

const int maxn = 103;

struct Edge{
    int from, to, w;
} E[maxn* maxn];
int N, M;

int fa[maxn];
void init(){
    for (int i=1;i<=M;i++) fa[i] = i;
}
int Find(int x){
    if (x == fa[x]) return x;
    return fa[x] = Find(fa[x]);
}
int Same(int x, int y){
    return Find(x)==Find(y);
}
void Union(int x, int y){
    int u = Find(x); int v = Find(y);
    if (u==v) return;
    fa[u] = v;
}
bool cmp(Edge a, Edge b){ return a.w < b.w; }
int kruskal(){
    int ans = 0;
    std::sort(E,E+N,cmp);
    for (int i=0;i<N;i++){
        if (Same(E[i].from, E[i].to)) continue;
        Union(E[i].from, E[i].to);
        ans += E[i].w;
    }
    return ans;
}

int main(){

    while (scanf("%d %d", &N,&M) == 2){
        if (N==0) break;
        init();
        for (int i=0;i<N;i++){
            scanf("%d %d %d", &E[i].from, &E[i].to, &E[i].w);
        }
        int res = 0;
        res = kruskal();
        for (int i=1; i<=M;i++){
            if (!Same(i, 1)) res = -1;
        }
        if (res == -1) 
            printf("?\n");
        else 
            printf("%d\n", res);
    }

}