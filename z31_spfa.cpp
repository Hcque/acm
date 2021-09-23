#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 210;
const int INF = 1e9;
int in_que[maxn], dist[maxn];
queue<int> que;
struct Edge{
    int to, w;
    Edge(){}
    Edge(int _t,int _w):to(_t),w(_w){}
};
vector<Edge> E[maxn];
int n,m,s,t;
void init(){
    for (int i=0;i<maxn;i++) E[i].clear();
}

int spfa(int &s){
    fill(in_que,in_que+maxn,0);
    fill(dist,dist+maxn,INF);
    que.push(s); in_que[s]=1; dist[s]=0;
    while(que.size()){
        auto now = que.front(); que.pop();
        in_que[now]= 0;

        for (int i=0;i<E[now].size();i++){
            int v = E[now][i].to;
            int w = E[now][i].w;
            if(dist[v] > dist[now]+w){
                dist[v] = dist[now]+w;
                if (!in_que[v]){
                    in_que[v]=1;
                    que.push(v);
                }
            }
        }
    }
    if (dist[t]!=INF) return dist[t];
    else return -1;
}

int main(){
    while (scanf("%d%d", &n,&m) == 2){
        init();
        while (m--){
            int a,b ,c;
            scanf("%d%d%d", &a,&b,&c);
            E[a].push_back(Edge(b,c));
            E[b].push_back(Edge(a,c));
        }
        scanf("%d%d", &s, &t);
        cout << spfa(s) << endl;
    }
}