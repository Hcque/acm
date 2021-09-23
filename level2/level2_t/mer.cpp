
// memcpy sizeof int
// ac

#include <iostream> 
#include <cstring>
using namespace std;
const int N = 1e6+10;
int n, q[N], tmp[N];

void m_s(int q[], int l, int r){
    if (l >= r) return;
    int mid = (l+r)>>1;
    m_s(q,l,mid );
    m_s(q,mid+1,r);

    int k=0,i=l,j=mid+1;
    while (i <= mid && j <= r){
        if (q[i] < q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];
    } 
    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    // for (int i=l,j=0;i<=r;i++,j++) q[i] = tmp[j];
    memcpy(q+l,tmp,(r-l+1) * sizeof(int));
}
int main(){
    scanf("%d", &n);
    for (int i=0;i<n;i++) scanf("%d", &q[i]);
    m_s(q,0,n-1);
    for (int i=0;i<n;i++) printf("%d ", q[i]);

}