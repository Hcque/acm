
// https://www.youtube.com/watch?v=0jWeUdxrGm4&ab_channel=Errichto

// https://www.spoj.com/submit/RMQSQ/

#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 100004
#define LOG 17
int a[MAXN], m[MAXN][LOG];

int query(int x, int y){
    int len = y-x+1;
    int k =0;
    while ( (1<<k)<=len  ){
        k++;
    }
    k--;
    return min(m[x][k], m[y-(1<<k)+1][k]);
}

int main()
{
    int N;
    cin >> N;
    for (int i=1;i<=N;i++){
        cin >> a[i];
        m[i][0] = a[i];
    }
    for (int k=1;k<LOG;k++){
        for (int i=1;i+(1<<k)-1<=N;i++){
            m[i][k] = min(m[i][k-1], m[i+(1<<(k-1))][k-1]);
        }
    }
    // for (int k=0;k<LOG;k++){
    //     for (int i=1;i+(1<<k)-1<=N;i++){
    //         cout << m[i][k] << " ";
    //     }
    //     cout << endl;
    // }
    int q;
    cin >> q;
    int L, R;
    for (int i=0;i<q;i++){
        cin >> L >> R;
	cout << query(L+1, R+1) << endl;
    }
    return 0;
}
