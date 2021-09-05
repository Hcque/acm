//0MS	1432K
// 15MS	1440K


#include <vector>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 200+10;
struct Edge{
    int to, w;
};
int s, t;

std::vector<Edge> E[maxn];
int dist[maxn], vis[maxn];

const int INF = 1e9;
typedef std::pair<int,int> PII;
// std::priority_queue<PII, std::vector<PII>,std::greater<PII>> heap;
queue<int> que;
void init(){
    for (int i=0;i<maxn;i++){
        E[i].clear();
	dist[i] = INF;
	vis[i] = 0;
    }
	while (que.size()) que.pop();
}

int dijk(int &s){
    dist[s] = 0;
    // heap.push({0, s});
	que.push(s); vis[s] = 1;
    while (que.size()){
        int now = que.front(); que.pop();

	for (int i=0;i<E[now].size(); i++){
	    int v = E[now][i].to;
	    int w = E[now][i].w;
	    if (dist[v] > dist[now]+w){
	        dist[v] = dist[now]+w;
		que.push(v);

	    }

	}

    }
    if (dist[t]<INF)
		return dist[t];
    else return -1;

    

}

int main()
{
    int n, m;
    while (scanf("%d%d", &n,&m)!=EOF){

		// cout << m << endl;
		init();

	    while (m--){
		int a, b, w;
		scanf("%d%d%d", &a,&b,&w);
		E[a].push_back({b, w});
		E[b].push_back({a, w});
	    }
	    scanf("%d%d", &s, &t);
	    printf("%d\n", dijk(s));
	}

}
