
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

const int N=1010, M=2000010;
int n,m;

int h[N], rh[N], e[M], w[M], ne[M], idx;
int dist[N], f[N], vis[N];
int S,T,K;
void add(int* h, int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dijkstra(){
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    memset(dist, 0x3f, sizeof(dist));
    dist[T] = 0;
    heap.push({0,T});
    while (!heap.empty()){
        int now = heap.top().second;
        int dd = heap.top().first;
        heap.pop();
        if (vis[now]) continue;
        vis[now] = 1;

        for (int i=rh[now];~i;i=ne[i]){

            int v = e[i];
            if (dist[v] > dist[now] + w[i]){
                dist[v] = dist[now]+w[i];
                heap.push({dist[v],v});
            }
        }
    }
    memcpy(f, dist, sizeof(f));
}

int a_star(){
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({f[S], {0, S}});
    memset(vis,0,sizeof(vis));

    while (heap.size()){
        // cout << heap.size() << endl;
        auto t = heap.top(); heap.pop();
        int now = t.second.second;
        int dis = t.second.first;
        
        if (vis[now] >= K) continue;
        vis[now]++;
        if ( now == T && vis[now] == K) return dis;

        for (int i=h[now]; ~i; i=ne[i]){
            int v = e[i];
            if (vis[v] < K){
                heap.push({dis+w[i]+f[v] , {dis+w[i], v}});
            }
        }
    }
    return -1;
}

int main()
{
    scanf("%d%d", &n,&m);
    memset(h,-1,sizeof(h));
    memset(rh,-1,sizeof(rh));
    while (m--){
        int a,b, c;
        scanf("%d%d%d", &a,&b,&c);
        add(h, a,b,c);
        add(rh, b,a,c);
    }
    scanf("%d%d%d", &S,&T,&K);
    if (S==T)K++;
    dijkstra();
    printf("%d\n", a_star());
}