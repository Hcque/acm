// -1%6

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1e6+10;
const int maxH = 999983;
struct flake{
    ll snow[6];
} arr[maxn];

class HashTable{
public:
    ll snow[6];
    HashTable* next;
    HashTable(){ next = 0; }
} H[maxH];

int _hash(ll x[6]){
    ll ans = 0;
    for (int i=0;i<6;i++){
        ans += x[i]%maxH;
    }
    return ans%maxH;
}

int cmp(ll x[6], ll y[6]){
    int r = 0;
    while (r <= 5){
        int i=0;
        for (i=0;i<6;i++){
            if (x[i] != y[(i+r)%6]){
                r++;
                break;
            }
        }
        if (i==6) return 1;
    }
    r = 0;
     while (r <= 5){
        int i=0;
        for (i=0;i<6;i++){
                // cout <<i << "|" << x[i] << "|" << y[(r-i)%6] << endl;
            if (x[i] != y[(-i+r+6)%6]){
                r++;
                break;
            }
        }
        if (i==6) return 1;
    }
    return 0;
}
// -1 find same
// 0 no same
int ins(ll x[6]){
    int k = _hash(x);
    if (H[k].snow[0] == 0){
        memcpy(H[k].snow, x,6*sizeof(ll));
    }
    else {
        HashTable* now = &H[k];
        while (now){
            if (cmp(now->snow, x)){
                return -1;
            }
            now = now->next;
        }
        now = new HashTable();
        memcpy(now->snow, x, 6*sizeof(ll));
    }
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        for (int j=0;j<6;j++){
            scanf("%lld", &arr[i].snow[j]);
        }
        int ans = ins(arr[i].snow);
        if (ans == -1){
            cout << "Twin snowflakes found." << endl;
            return 0;
        }
    }
    cout << "No two snowflakes are alike." << endl;
    return 0;
}


