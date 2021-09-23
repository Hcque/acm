

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5+10;

struct Node
{
    int son[2], val, p;
    int size, flag;
    void init(int _p, int _v)
    {
        p = _p, val = _v;
    }
} tr[N];
void pushup(int u)
{
    tr[u].size = 1 + tr[tr[u].son[0]].size + tr[tr[u].son[1]].size;
}

void pushdown(int u)
{
    if (tr[u].flag)
    {
        swap(tr[u].son[0], tr[u].son[1]);
        tr[tr[u].son[0]].flag ^= 1;
        tr[tr[u].son[1]].flag ^= 1;
        tr[u].flag = 0;
    }
}

void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[x].son[1] == x;
    tr[z].son[ tr[z].son[1] == y ] = x; tr[x].p = z;
    tr[y].son[k] = tr[x].son[k^1]; tr[tr[x].son[k^1]].p = y;
    tr[x].son[k^1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;

    }
}

void output(int u)
{
    pushdown(u);
    if (tr[u].son[0]) output(tr[u].son[0]);
    if (1<= tr[u].val && tr[u].v <= n) printf("%d ", tr[u].val);
    if (tr[u].son[0]) output(tr[u].son[0]);
}
int main()
{

}