#include <iostream>
using namespace std;

const int N = 2e5+10;
int m,p;
struct Node
{
    int l,r,val;
} L[N*4];

void build(int u, int l, int r)
{
    L[u] = {l,r};
    if (l==r) return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
}

void pushup(int u)
{
    L[u].val = max(L[u<<1].val , L[u<<1|1].val);
}

int query(int u, int l, int r)
{
    if (l<=L[u].l && L[u].r <= r) return L[u].val;
    int mid = L[u].l + L[u].r >> 1;
    int ans = 0;
    if (l <= mid) ans = query(u<<1, l,r);
    if (r >mid) ans = max(ans, query(u<<1|1, l,r));
    return ans;
}
void modify(int u, int x, int v)
{
    if (L[u].l == L[u].r && L[u].l == x) L[u].val = v;
    else {
        int mid = L[u].l + L[u].r >> 1;
        if (x<= mid) modify(u<<1, x, v);
        else modify(u<<1|1,x,v);
        pushup(u);
    }
}
int main()
{
    cin >> m >> p;
    build(1,1,m);

    int n = 0, last = 0;
    while (m--)
    {
        char op[2];
        int x;
        cin >> op >> x;
        if (op[0] == 'Q'){
            last = query(1,n-x+1,n);
            printf("%d\n", last);
        }
        else {
            modify(1,n+1,(x+(long long)last)%p);
            n++;
        }
    }

}