
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int n, a[N];

void qs(int l, int r)
{
    // cout << l << r << endl;
    if (l >= r) return;
    
    int pivot = a[r];
    int i = l-1, j = l;
    
    
    for (;j<r;j++)
    {
        if (a[j] < pivot) swap(a[++i],a[j]);
    }
    swap(a[i+1],a[r]);
    
    qs(l,i);
    qs(i+2,r);
    
    
}


int main()
{
    
    cin >> n;
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    
    qs(0,n-1);
    
    for (int i = 0; i < n; i ++ ) cout << a[i] << " ";
}
