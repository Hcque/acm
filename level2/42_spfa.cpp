

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1e5+10;

typedef pair<int,int> PII;

int n,m;
int h[N],w[N], e[N],ne[N], idx;
int dist[N];
bool vis[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);

    vis[1] = true;

    while (q.size())
    {
        int t = q.front(); q.pop();
        vis[t] = false;
        for (int i = h[t];~i;i=ne[i])
        {
            int j = e[i];
            if(dist[j]> dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if(!vis[j])
                {
                    q.push(j);
                    vis[j] = true;
                }
            }
        }
    }
    
        

}
int main()
{
    scanf("%d%d", &n,&m);
    memset(h, -1, sizeof h);

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a,&b,&c);
        add(a,b,c);
    }

    int t = dijk();
    printf("%d\n", t);

}



