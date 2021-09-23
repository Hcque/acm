// 830

#include <iostream>
using namespace std;

const int N = 1e5+10;
int stk[N], tt;
int n;

int main()
{
    cin >> n;
    for (int i=0;i<n;i++)
    {
        int x;
        cin >>x;
        while (tt && stk[tt]>=x) tt--;
        if (tt) printf("%d ",stk[tt]);
        else printf("-1 ");

        stk[++ tt] = x;
    }
}