// 1996K	438MS

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int N;
const int maxn = 502;

struct Edge{
    int to, dist;
    Edge(){}
    Edge(int _t, int _d): to(_t), dist(_d) {}
    bool operator<(const Edge& b) const {
        return b.dist < dist;
    }
};
vector<Edge> G[maxn];
int vis[maxn];
priority_queue<Edge> que;

void init(){
    for (int i=0;i<maxn;i++){
        G[i].clear();
	vis[i] = 0;
    }
    while (que.size()) que.pop();
}

int prim(){
    int ans = 0;
    vis[0] = 1;
    for (int i=0;i<G[0].size();i++){
        que.push(G[0][i]);
    }
    while (!que.empty()) {
        Edge e = que.top(); que.pop();
	if (vis[e.to]) continue;
	vis[e.to] = 1;
	ans = max( e.dist, ans);
	for (int i=0;i<G[e.to].size();i++){
	    que.push(G[e.to][i]);
	}
    }
    return ans;
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        init();
    	scanf("%d", &N);
	for (int i=0;i<N;i++){
	    for (int j=0;j<N;j++){
	    	int tmp;
	        scanf("%d", &tmp);
		G[i].push_back(Edge(j,tmp) );
		G[j].push_back(Edge(i,tmp) );
		// std::cout << tmp << " ";
	    }

	}
	int res = prim();
	printf("%d\n", res);

    }
}
