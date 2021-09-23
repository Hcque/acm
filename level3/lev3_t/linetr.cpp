
#include <iostream>
using namespace std;

const int N = 2e5+10;
int m, p;
struct Node{
    int l, r, v;
} tr[N*4];

void build(int u, int l, int r)
{
    tr[u] = {l,r};
    if (l==r) return;
    int mid= l+r>>1;
    build(u<<1, l,mid);
    build(u<<1|1, mid+1, r);
}

void pushup(int u)
{
    tr[u].v = max(tr[u<<1].v, tr[u<<1|1].v);
}

int query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].v;
    int mid = tr[u].l+tr[u].r >> 1;
    int ans = 0;
    if (l<=mid) ans = query(u<<1, l, r);
    if (r > mid) ans = max(ans, query(u<<1|1, l, r));
    return ans;
}

void modify(int u, int x,int v)
{   
    if (tr[u].l == tr[u].r && tr[u].l == x) tr[u].v = v;
    else {
        int mid= tr[u].l+tr[u].r>>1;
        if (x<=mid) modify(u<<1, x, v);
        else modify(u<<1|1, x, v);
        pushup(u);
    }
}
int main()
{
    int n = 0, last = 0;
    cin >> m >> p;
    build(1, 1, m);
    while (m--)
    {
        char op[2];int x;
        cin >> op >> x;
        if (op[0] == 'Q'){
            last = query(1, n-x+1, n);
            printf("%d\n", last);
        }
        else {
            modify(1, n+1, ((long long)last + x)%p);
            n++;
        }

    }

}