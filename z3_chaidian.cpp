// ac

// c >= w
//memset h = -1;

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 1e3+10;
const int maxm = 1e6+10;
const int maxc = 1e2+10;

int C,S,E;
int n,m, price[maxn];

int h[maxn], e[maxm], ne[maxm], w[maxm], idx;
void add(int a, int b, int c){
    w[idx]=c,e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

struct Ver{
    int d,u,c;
    bool operator<(const Ver& b) const { return d>b.d; }
};
int dist[maxn][maxc];
int dijk(int contain,int start,int end){
    priority_queue<Ver> heap;
    memset(dist,0x3f,sizeof(dist));
    dist[start][0] = 0;
    heap.push({0,start,0});

    while (heap.size()){
        auto t = heap.top();heap.pop();
        if (t.u == end) return t.d;

        if (t.c<contain){
            if (dist[t.u][t.c+1] > dist[t.u][t.c] + price[t.u] )
                dist[t.u][t.c+1] = dist[t.u][t.c] + price[t.u];
                heap.push({dist[t.u][t.c+1], t.u,t.c+1});
        }
        for (int i=h[t.u];~i;i=ne[i]){
            int v = e[i];
            if (t.c>=w[i]){
            if (dist[v][t.c-w[i]] > dist[t.u][t.c]){
                dist[v][t.c-w[i]] = dist[t.u][t.c];
                heap.push({dist[v][t.c-w[i]],v,t.c-w[i]});
            }
            }
        }
    }
    return -1;
}
int main(){
    scanf("%d%d", &n,&m);
    for (int i=0;i<n;i++) scanf("%d", &price[i]);

    memset(h,-1,sizeof(h));
    while (m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c);
        add(b,a,c);
    }
    int query;
    scanf("%d", &query);
    while (query--){

    scanf("%d%d%d", &C,&S,&E);
    int ans = dijk(C,S,E);
    if (ans == -1) printf("impossible\n");
    else printf("%d\n", ans);

    }

    return 0;
}