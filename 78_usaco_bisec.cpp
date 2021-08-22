//http://www.usaco.org/index.php?page=viewproblem2&cpid=991&lang=zh
// http://www.usaco.org/current/data/sol_loan_silver_jan20.html


// failed


#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
ll N, K, M;
bool valid(ll x){
    // cout << x << endl;

    ll given = 0;
    ll day = 0;
    ll Y = (N - given) / x;
    if (Y < M) {
        return K*M >= N;
    }
    else if (Y*K < N) return false;
    else {


    while (day < K){
        // cerr<<i<<endl;
        ll Y = (N - given) / x;
        if (Y < M) 
            return (K-day)*M >= (N - given);
        // cerr << "Y" << Y << endl;
        ll numdays = (N - given) / Y ;
        // cout << numdays << "|" << K << endl;
        if (numdays > K-day) numdays = K-day;
        day += numdays;
        given += Y * numdays;
        if (given >= N) return true;
    }    
    return given >= N;
    }
}

int main()
{
    // freopen("loan.in", "r", stdin);
    // freopen("loan.out", "w", stdout);
    cin >> N >> K >> M;

    ll x = 1;
    ll lo = 1;
    ll hi = N;
    ll mid;
    while (lo <= hi){
        mid = lo+(hi-lo)/2;
        // cerr << mid << endl;
        if (valid(mid)){
            // cerr << mid << endl;
            lo = mid+1;
            x = max(x, mid);
        }
        else hi = mid-1;
    }
    cout << x;
}