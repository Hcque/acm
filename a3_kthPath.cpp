#include <iostream>
using namespace std;
const int maxn = 1e3+10;
const int maxm = 1e5 + 10;

int Head[maxn], to[maxn], w[maxm], Next[maxm], tot;

void add(int *h, int x, int y, int z){
    w[tot] = z;
    to[tot] = y;
    Next[tot] = Head[x];
    Head[tot] = tot++;
}

int main()
{
    // int N, M;
    // cin >> N >> M;
    // for(int i=0;i<M;i++){
    //     int A, B, L;
    //     cin >> A >> B >> L;

    // }
    // int S, T, K;
    // cin >> S >> T >> K;


}