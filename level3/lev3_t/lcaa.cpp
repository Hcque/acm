#include <iostream>

using namespace std;

const int N = 4e4+10, M = N;
int h[N], e[M], ne[M], idx;
int n,m;
int root;
int fa[N], vis[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}


int query(int a, int b)
{
    while (fa[a] != -1){
        vis[a] = 1;
        a = fa[a];
    }
    while (fa[b] != -1){
        if (vis[b] == 1) return b;
        b = fa[b];
    }
    return -1;
}


int main()
{
    scanf("%d", &n);

    for (int i=0;i<n;i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        fa[a] = b;
        /*
        if (b==-1) root = a;
        else{
            add(a, b);
        }
        */
    }
    scanf("%d", &m);
    while (m--)
    {
        printf("%d\n", query(a, b));
    }
}

