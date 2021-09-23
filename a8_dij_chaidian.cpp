
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

const int N = 1e3+10;
const int M = 2e5+10;
const int C = 1e3+10;

int n,m;
int h[N], e[M], ne[M],w[M],idx;
int price[N];
int dist[N][C], vis[N][C];
struct Ver{
    int d, u, c;
    bool operator<(const Ver& b)const { return d>b.d; }
};
void add(int a, int b, int c){
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

int dijk(int c, int start, int end){
    priority_queue<Ver> heap;
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    heap.push({0,start,0}); dist[start][0] = 0;

    while (heap.size()){
        auto t = heap.top(); heap.pop();

        if (t.u == end) return t.d;
        if (vis[t.u][t.c]) continue;
        vis[t.u][t.c] = 1;  

        if (t.c<c){ // add oil
            if (dist[t.u][t.c+1] > dist[t.u][t.c] + price[t.u]){
                dist[t.u][t.c+1] = dist[t.u][t.c] + price[t.u];
                heap.push({dist[t.u][t.c+1], t.u, t.c+1});
            }
        }
        for (int i=h[t.u]; ~i;i=ne[i]){
            int v = e[i];
            if (t.c >= w[i]){ // oil consume
                if (dist[v][t.c-w[i]] > dist[t.u][t.c] ){
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
    for (int i=0;i<n;i++) scanf("%d",&price[i] );
    memset(h,-1,sizeof(h));
    while (m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c); add(b,a,c);
    }

    int query; scanf("%d", &query);

    while (query--){
        int c,s,t;
        scanf("%d%d%d", &c,&s,&t);
        int ans = dijk(c,s,t);
        if (ans == -1)printf("impossible\n");
        else printf("%d\n", ans);
    }
    return 0;
}
