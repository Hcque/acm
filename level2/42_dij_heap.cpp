

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
int dijk()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    priority_queue<PII,vector<PII>, greater<PII> heap;
    heap.push({0,1});
    while (heap.size())
    {
        auto t = heap.top(); heap.pop();
        int ver = t.second, distance = t.first;

        if (vis[ver]) continue;

        for (int i = h[ver]; ~i;i=ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push(dist[j], j);
            }

        }

    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
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


