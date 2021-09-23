#include <iostream>
using namespace std;

const int MAXN = 1e5+5;
const int MAXE = MAXN*2;
struct E{
    int to, next;
} Edge[MAXN];
int tot, Head[MAXN];
inline void addEdge(int u, int v){
    Edge[tot].to = v;
    Edge[tot].next = Head[u];
    Head[u] = tot++;

    Edge[tot].to = u;
    Edge[tot].next = Head[v];
    Head[v] = tot++;
}

int fa[MAXN], depth[MAXN], size[MAXN], hchild[MAXN],

void dfs1(int u, int f){
   fa[u] = f;
   depth[f] = 1 + depth[u];
}

int cnt, dfsn[MAXN], top[MAXN], w[MAXN];
void dfs2(int u, int t){
    dfsn[u] = ++cnt;
    top[u] = t;

}

int main(){
    int N, M, R, P;
    cin >> N >> M >> R >> P;
    int tmp;
    for (int i=0;i<N;i++){
        cin >> tmp;
    }

    for (int i=1;i<=N-1;i++){
        int x, y;
        cin >> x >> y;
        addEdge(x,y);
    }
    for (int i =0;i<M;i++){
        int op, x, y, z;
        cin >> op;
        switch (op){
            case 1:
            case 2:
            case 3:
            case 4:

        }
    }


}

