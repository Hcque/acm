// add dT
// maxnM

//ac

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1e3+10, M = 2e4+10;
int n,m,S,T;

int h[N], e[M],ne[M],f[M],idx;
void add(int a,int b, int c){
    e[idx]=b,f[idx]=c,ne[idx]=h[a],h[a]=idx++;
    e[idx]=a,f[idx]=0,ne[idx]=h[b],h[b]=idx++;
}

int vis[N], d[N], pre[N];
bool bfs(){
    queue<int> que;
    memset(vis,0,sizeof(vis));
    que.push(S); vis[S]=1; d[S]=1e9;
    while (que.size()){
        // cout << que.size();
        auto now = que.front();que.pop();
        for (int i=h[now];~i;i=ne[i]){
            int v = e[i];
            if (f[i] && !vis[v]){
                vis[v] = 1;
                pre[v] = i;
                d[v] = min(d[now], f[i]);
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
        for (int i=T;i!=S;i=e[pre[i]^1]){
            f[pre[i]] -= d[T], f[pre[i]^1] += d[T];
        }
    }
    return ans;
}

int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    memset(h,-1,sizeof(h));
    while(m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c);
    }
    cout << EK() << endl;
    return 0;
}