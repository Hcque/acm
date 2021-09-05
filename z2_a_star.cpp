#include <queue>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3+10;
const int maxm = 2e6+10;

int n, m, S,T,K;
int Head[maxn], rHead[maxn], Next[maxm], w[maxm], To[maxm], idx;
int dist[maxn], f[maxn],vis[maxn];

void add(int *h,int a, int b, int c){
    To[idx]=b,w[idx]=c,Next[idx]=h[a],h[a]=idx++;
}

typedef pair<int,int> PII;
const int INF = 1e9;
void dijk(){
    fill(dist,dist+maxn, INF);
    priority_queue<PII,vector<PII>,greater<PII>> heap;
    heap.push({0,T});
    dist[T]=0;
    while (heap.size()){
        auto tmp = heap.top();heap.pop();
        int dis = tmp.first;
        int now = tmp.second;
        for (int i=rHead[now];~i;i=Next[i]){
            int v = To[i];
            if (dist[v] > dis + w[i]){
                dist[v] = dis+ w[i];
                heap.push({dist[v], v});
            }
        }
    }
    memcpy(f, dist,sizeof(f));
}
typedef pair<int, PII> PIII;

int Astar(){
    memset(vis, 0, sizeof(vis));
    priority_queue<PIII,vector<PIII>,greater<PIII>> heap;
    heap.push({f[S],{0,S}});
    while (heap.size()){
        auto tmp = heap.top();heap.pop();
        int dis = tmp.second.first;
        int now = tmp.second.second;

        if (vis[now] > K) continue;
        vis[now]++;
        if (now==T && vis[now]==K) return dis;
        for (int i=Head[now];~i;i=Next[i]){
            int v = To[i];
            if (vis[v]<=K){
                heap.push({f[v]+dis+w[i],{dis+w[i], v}});
            }
        }
    }
    return -1;
}
int main(){
    scanf("%d%d", &n,&m);
    memset(Head,-1,sizeof(Head));
    memset(rHead,-1,sizeof(rHead));
    while (m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(Head,a,b,c);
        add(rHead,b,a,c);
    }

    scanf("%d%d%d",&S,&T,&K);
    if (S==T)K++;
    dijk();
    printf("%d\n", Astar());
}

