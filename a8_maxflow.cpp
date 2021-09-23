
//https://www.acwing.com/problem/content/2173/


#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
queue<int> q;
const int N = 1e3+10, M = 2e5+10, INF = 1e8;

int  n,m,S,T;
int h[N], e[M], f[M], ne[M], idx;

int d[N], pre[N];
int vis[N];

void add(int a, int b, int c){
    e[idx]=b,f[idx]=c,ne[idx]=h[a],h[a]=idx++;
    e[idx]=a,f[idx]=0,ne[idx]=h[b],h[b]=idx++;
}

bool bfs(){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(S); vis[S]=1,d[S]=INF;
    while (q.size()){
        auto tmp = q.front();q.pop();
        for (int i=h[tmp];~i;i=ne[i]){
            int v = e[i];
            if (!vis[v] && f[i]){ // !
                vis[v]=1;
                pre[v]=i;
                d[v] = min(d[tmp],f[i]);
                if (v==T) return true;
                q.push(v);
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
    scanf("%d%d%d%d", &n,&m,&S,&T);
    memset(h,-1,sizeof(h));
    while (m--){
        int a,b,c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c); 
    }

    cout << EK() << endl;
    return 0;
}


