// head
// dist T = 0


#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e3+10;
const int maxm = 2e6+10;
int n,m;
int S,T,K;
int Head[maxn], rHead[maxn], Next[maxm], w[maxm], To[maxm], idx;

int dist[maxn], f[maxn], vis[maxn];
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

void add(int *h, int a, int b, int c) {
    To[idx] = b, w[idx] = c, Next[idx] = h[a], h[a]=idx++;
}
void dijk()
{
    fill(dist, dist+maxn, 1e9);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, T});
	dist[T] = 0;
    while (heap.size()) {
        auto tmp = heap.top(); heap.pop();
	int now = tmp.second;
	int dis = tmp.first;

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


int Astar(){

    memset(vis,0,sizeof(vis));

    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({f[S],{0,S}});
    while (heap.size()) {
        auto tmp = heap.top(); heap.pop();
	int now = tmp.second.second;
	int dis = tmp.second.first;

	if (vis[now] > K) continue;
	vis[now]++;
	if (now == T && vis[now] == K){
	    return dis;
	}

	for (int i=Head[now]; ~i;i=Next[i]){
	    int v = To[i];
	    if (vis[v] <= K){
		heap.push({w[i]+dis+f[v], {w[i]+dis, v}});
	    }
	}
	}
	return -1;
}

int main(){
    scanf("%d%d", &n,&m);

    memset(Head, -1, sizeof(Head));
    memset(rHead, -1, sizeof(rHead));
    while (m--){
	int a, b, c;
        scanf("%d%d%d", &a,&b,&c);
	add(Head,a,b,c);
	add(rHead,b,a,c);
    }
    scanf("%d%d%d", &S,&T,&K);
    if (S==T)K++;
    dijk();
    printf("%d\n", Astar());

}
