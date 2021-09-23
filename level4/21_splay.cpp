
// https://www.acwing.com/problem/content/2439/


#include <iostream>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;
int n,m;
struct Node
{
    int s[2], p, v;
    int size, flag;
    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
    }
} tr[N];
int root, idx;

void pushup(int u)
{
   tr[u].size = 1 + tr[tr[u].s[0]].size + tr[tr[u].s[1]].size;
}

void pushdown(int u)
{
    if (tr[u].flag)
    {
        swap(tr[u].s[0], tr[u].s[1]);
        tr[tr[u].s[0]].flag ^= 1;
        tr[tr[u].s[1]].flag ^= 1;
        tr[u].flag = 0;
    }
}
void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k^1], tr[tr[x].s[k^1]].p = y;
    tr[x].s[k^1] = y,tr[y].p = x;
    pushup(y); pushup(x);
}

void splay(int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v,p);
    splay(u,0);
}

int get_k(int k)
{
    int u = root;
    while (1)
    {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1]; 
    }
    return -1;
}

void output(int u)
{
    pushdown(u);
    if (tr[u].s[0]) output(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if (tr[u].s[1]) output(tr[u].s[1]);
}


int main()
{
    scanf("%d%d", &n,&m);
    for (int i = 0;i<=n+1;i++) insert(i);
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(l), r = get_k(r+2);
        splay(l,0), splay(r,l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(root);

}

