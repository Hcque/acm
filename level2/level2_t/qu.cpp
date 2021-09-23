#include <iostream>
using namespace std;
const int N = 1e6+10;
int n,q[N];

void q_s(int q[], int l, int r){
    if (l>=r) return;
    int x = q[(l+r)>>1], i = l-1, j = r+1;
    while (i<j){
        do i++; while (q[i]< x);
        do j--; while (q[j]>= x);
        if (i < j) swap(q[i],q[j]);
    }
    // cout << l << i << "|" << j  << r<< endl;
    q_s(q,l,j);
    q_s(q,j+1,r);
}

int main(){
    scanf("%d", &n);
    for (int i=0;i<n;i++) scanf("%d", &q[i]);
    q_s(q,0,n-1);
    for (int i=0;i<n;i++) printf("%d ", q[i]);
}