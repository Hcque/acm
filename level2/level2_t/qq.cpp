#include <iostream>
using namespace std;

const int N = 1e5+10;
int n, q[N];



// void qs(int q[], int l, int r){
//     if (l>=r) return;
//     int x = q[(l+r)>>1], i = l-1,j = r+1;
//     while (i<j){
//         do i++ ; while (q[i]<x);
//         do j-- ; while (q[j]>x);
//         if (i < j) swap(q[i],q[j]);
//     }
//     qs(q, l, j);
//     qs(q, j+1, r);
// }
void qs(int q[], int l, int r){

    if (l>= r) return;
    int i = l-1, j = r+1;
    int x = q[(l+r)>>1];
    while (i<j){
        do i++; while (q[i]<x);
        do j--; while (q[j]>x);
        swap(q[i], q[j]);
    }
    qs( q, l, j);
    qs( q, j+1, r);
}
int main()
{
    cin >> n;
    for (int i=0;i<n;i++) cin >> q[i];
    qs(q, 0, n-1);
    for (int i=0;i<n;i++) cout << q[i] << " ";

}