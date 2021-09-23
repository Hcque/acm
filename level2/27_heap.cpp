#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;
int n,m;
int h[N], sz;

void down(int u)
{
    int t = u;
    if (u*2 <= sz && h[u*2]<h[t]) t = u*2;
    if (u*2+1 <= sz && h[u*2+1]<h[t]) t = u*2+1;
    if (u != t)
    {
        swap(h[u], h[t]);
        down(t);
    }
}

void up(int u)
{
    while ( u/2 && h[u/2] > h[u])
    {
        swap(h[u/2],h[u]);
        u /= 2;
    }

}
int main()
{
    scanf("%d%d", &n,&m);
    for (int i =1;i<=n;i++ ) scanf("%d", &h[i]);
    sz = n;

    for (int i = n/2; i;i--) down(i);
    while (m--)
    {
        printf("%d ", h[1]);
        h[1] = h[sz];
        sz--;
        down(1);
    }
}
