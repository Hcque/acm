//
// << para
// t 



#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5+10;
int n,m;
int q[N], sz;

void down(int u)
{
    int t = u;
    if (u<<1 <= sz && q[u<<1] < q[t]) t = u<<1;
    if ((u<<1|1) <= sz && q[u<<1|1] < q[t]) t = u<<1|1;
    if (u != t)
    {
        swap(q[u], q[t]);
        down(t);
    }
}

// void down(int u)
// {
//     int t = u;
//     if (u*2 <= sz && q[u*2]<q[t]) t = u*2;
//     if (u*2+1 <= sz && q[u*2+1]<q[t]) t = u*2+1;
//     if (u != t)
//     {
//         swap(q[u], q[t]);
//         down(t);
//     }
// }

int pop()
{
    int ans = q[1];
    swap(q[1], q[sz]);
    sz--;
    down(1);
    return ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &q[i]);
    sz = n;

    for (int i = n/2; i; i--) down(i);

    while (m--)
    {
        printf("%d ", pop());
    }

}