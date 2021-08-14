#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
#define MAXN 200003

int N, K;
int vis[MAXN];
typedef pair<int, int> p;
queue<p> que;
void bfs()
{
    que.push(p(N,0));
    vis[N] = 1;
    while (!que.empty()){
        p pp = que.front(); que.pop();
        int n = pp.first;
        int c = pp.second;
        if (n == K) {
            printf("%d\n", c);
            break;
        }
        if (n<=K && !vis[n+1]){
            que.push(p(n+1,c+1));
            vis[n+1] = 1;
        }

        if (n >= 0 && !vis[n-1]){
            que.push(p(n-1, c+1));
            vis[n-1] = 1;
        }
        if (n<=K  && !vis[n*2]){
            que.push(p(n*2, c+1));
            vis[n*2] = 1;
        }
    }
}


int main()
{
    cin >> N >> K;
    memset(vis, 0, sizeof(vis));

    bfs();
    return 0;
}

