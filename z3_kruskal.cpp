// 0MS	1384K
// init fa

#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 103;
class Edge{
public:
    int from, to, w;
    bool operator<(const Edge& b)const { return w<b.w; }
};
Edge E[maxn*maxn];
int m,n, fa[maxn];

void init(){
    for (int i=0;i<maxn;i++){
        fa[i] = i;
    }
}
int Find(int x){
    if (x== fa[x]) return x;
    return fa[x] = Find(fa[x]);
} 

int Same(int x, int y){
    return Find(x) == Find(y);
}

void Union(int x, int y){
    int u = Find(x), v = Find(y);
    if (u==v) return;
    fa[u] = v;
}

int kruskal(){
    int ans = 0;
    sort(E+1,E+1+m);
    for (int i=1;i<=m;i++){
        if ( Same(E[i].from, E[i].to)) continue;
        ans += E[i].w;
        Union(E[i].from, E[i].to);
    }
    return ans;
}
int main(){
    while (scanf("%d%d",&m,&n)){
        if (m==0) break;
        init();

        int x,y,z;
        for (int i=1;i<=m;i++){
            scanf("%d%d%d", &E[i].from,&E[i].to,&E[i].w);
        }
        int res = kruskal();
        for (int i=1;i<=n;i++){
            if ( !Same(i,1) ) {
                res = -1;
                break;
            }
        }
        if (res==-1) printf("?\n");
        else printf("%d\n", res);
    }

}