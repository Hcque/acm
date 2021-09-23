 // x u modfiy

#include <iostream>
using namespace std;

const int N = 2e5+10;
int m,p;
typedef long long ll;
struct Node
{
    int l,r,v;
} lt[N*4];

void build(int u, int l,int r)
{
    lt[u] = {l, r};
    if(l==r) return;
    int mid = l+r >> 1;
    build(u<<1, l, mid);
    build(u<<1|1, mid+1, r);
}

void pushup(int u)
{
    lt[u].v = max( lt[u<<1].v , lt[u<<1|1].v);
}

int query(int u, int l, int r)
{
    if (l<= lt[u].l && lt[u].r <= r) return lt[u].v;
    int mid = lt[u].l + lt[u].r >> 1;
    int v = 0;
    if (l<= mid) v = query(u<<1, l,r);
    if (r >mid) v = max(v, query(u<<1|1, l,r));
    return v;
}

void modify(int u, int x, int v)
{
    if (lt[u].l == lt[u].r && lt[u].l == x) lt[u].v = v;
    else {
        int mid = lt[u].l + lt[u].r >> 1;
        if (x <= mid) modify(u<<1, x, v);
        else modify(u<<1|1, x, v);
        pushup(u);
    }
}
int main()
{
    int n = 0, last = 0;
    scanf("%d%d", &m,&p);

    build(1,1,m);
    while (m--)
    {
        char op[2]; int x;
        scanf("%s%d", op, &x);
        if (op[0] == 'Q') last = query(1,n-x+1,n), printf("%d\n",last);
        else modify(1,n+1, ((long long)last + x) % p), n++;
    }



}
