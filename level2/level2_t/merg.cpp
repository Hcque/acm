#include <iostream>
using namespace std;

const int N = 1e5+10;
int n, q[N], tmp[N];

void merg(int q[], int l, int r)
{

    if (l >= r) return;
    int mid = l+r>>1;
    merg(q,l,mid);
    merg(q,mid+1,r);
    int i = l, j = mid+1, k = 0;
    while (i <= mid && j <= r){
        if (q[i] < q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (int i=l, j=0;i<=r;i++, j++) q[i] = tmp[j];
}

int main()
{
    cin >> n;
    for (int i = 0;i < n; i++ ) cin >> q[i];
    merg(q, 0, n-1);
    for (int i = 0;i < n; i++ ) cout << q[i];
}