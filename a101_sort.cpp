
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5+10;
int a[maxn];

void 


int main(){

    int N;
     cin >> N;
     for (int i=0;i<N;i++){
         cin >> a[i];
     }

     sort(a,a+N);
     for (int i=0;i<N-1;i++) cout << a[i] << " ";
     cout << a[N-1];

}