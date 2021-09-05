// dist INF;
// dis cumm
// vis[i]/ vis[v]

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
const int maxN = 1e3+10;
const int maxM = 2e6+10;
int Head[maxN], rHead[maxN], Next[maxM], To[maxM], w[maxM], idx=0;
int dist[maxN], f[maxN], vis[maxN];
int S,T,K;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

void add(int *h, int a, int b, int c){
    To[idx]=b, w[idx]=c, Next[idx] = h[a], h[a]=idx++;
}

void dijk(){
    std::priority_queue<PII, vector<PII>, greater<PII>> heap;
    fill(dist, dist+maxN, 1e9);
    dist[T] =0;
    heap.push({0, T});
    while (heap.size()){
        auto tmp = heap.top();heap.pop();
        int now = tmp.second;

        for (int i=rHead[now]; ~i;i=Next[i]){
            int v = To[i];
            if (dist[v] > dist[now] + w[i]){
                dist[v] = dist[now] + w[i];
                heap.push({dist[v], v});
            }
        }
    }
    memcpy(f, dist, sizeof(f));
}

int a_star(){
    std::priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    memset(vis, 0, sizeof(vis));
    heap.push({f[S]+0,{0, S}});
    while (heap.size()){
        auto tmp = heap.top(); heap.pop();
        int now = tmp.second.second;
        int dis = tmp.second.first;
        if (vis[now] > K) continue;
        vis[now]++;
        if (now ==T && vis[now]==K)
            return dis;
        
        for (int i=Head[now];~i;i=Next[i]){
            int v = To[i];
            if (vis[i] < K)
                heap.push({ f[v]+dis+w[i], {dis+w[i], v}});
        }
    }
    return -1;
}

int main(){
    scanf("%d%d", &n, &m);
    memset(Head, -1, sizeof(Head));
    memset(rHead, -1, sizeof(rHead));
    while (m--){
	int a,b,c;
	scanf("%d%d%d", &a,&b,&c);
	add(Head,a,b,c); add(rHead,b,a,c);
    }
    scanf("%d%d%d", &S,&T,&K);
    if (S==T) K++;
    dijk();
    printf("%d\n", a_star());
}
