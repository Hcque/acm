#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1e3+10, M = 2e5+10, INF = 1e9;
int n,m,S,T;

int h[N],e[M],ne[M],idx,f[M];
void add(int a, int b, int c){
    e[idx]=b,f[idx]=c, ne[idx]=h[a],h[a]=idx++;
}

int vis[N],d[N],pre[N];
bool bfs(){
    queue<int> que;
    memset(vis,0,sizeof(vis));

    que.push(S), d[S]=INF, vis[S] =1;
    while (que.size()){
        int now = que.front();que.pop();
        
        for (int i=h[now];~i;i=ne[i]){
            int v = e[i];
            if (!vis[v] && f[i]){
                vis[v]=1;
                pre[v]=i;
                d[v]=min(d[now],f[i]);
                if (v == T) return true;
                que.push(v);
            }
        }
    }
    return false;
}
int EK(){
    int ans = 0;
    while (bfs()){
        ans += d[T];
        for (int i=T;i!=S;i=e[pre[i]^1])
            f[pre[i]] -= d[T], f[pre[i]^1] += d[T];
    }
    return ans;
}
int main(){
    scanf("%d%d%d%d", &n,&m,&S,&T);
    memset(h,-1,sizeof(h));
    while (m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c);
        add(b,a,0);
    }
    cout << EK() << endl;
}