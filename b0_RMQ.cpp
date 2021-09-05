#include <iostream>
#include <cmath>
using namespace std;

const int maxn = 1e5+10;
int arr[maxn];
int rmq[maxn][20];

int query(int lo, int hi){
    if (lo == hi) return arr[lo];
    int L = hi-lo+1;;
    int c = 0;
    while ((1<<c) <= L) c++;
    c--;
    // cout << c ;
    return min(rmq[lo][c], rmq[hi-(1<<c )+1][c]);
}

int main(){
    int N;
    cin >> N;
    for (int i=1;i<=N;i++){
        cin >> arr[i];
	rmq[i][0] = arr[i];
    }
    int c = 0;
    while ( (1<<c) <= N) c++;
    c--;
        for (int j=1;j<= c;j++){
    for (int i=1;i<=N-(1<<j)+1;i++){
	    rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
	}
    }

    int T;
    cin >> T;
    while (T--){
        int lo, hi;
	cin >> lo >> hi;
	lo++, hi++;
        cout << query(lo, hi) << endl;
    }
}
