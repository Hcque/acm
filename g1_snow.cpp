// -1%6
// pointer!!
//13176K	3313MS
//8476K	3532MS
//9656K	3032MS

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
// typedef long long ll;

const int maxn = 1e5+10;
const int maxH = 999997;
// struct flake{
//     ll snow[6];
// } arr[maxn];

class HashTable{
public:
    int snow[6];
    HashTable* next;
    HashTable(){ fill(snow,snow+6,0);next = 0; }
};

HashTable* H[maxH];
// void init(){
//     H.clear();
//     H.resize(maxn);
//     fill(H.begin(), H.end(), 0);
// }
int _hash(int x[6]){
    int ans = 0;
    for (int i=0;i<6;i++){
        ans += x[i]%maxH;
    }
    return ans%maxH;
}

int cmp(int x[6], int y[6]){
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
int ins(int x[6]){
    int k = _hash(x);
    if (!H[k]){
        H[k] = new HashTable();
        memcpy(H[k]->snow, x,6*sizeof(int));
    }
    else {
        HashTable* now = H[k];
        while (now){
            if (cmp(now->snow, x)){
                return -1;
            }
            now = now->next;
        }
        now = new HashTable();
        memcpy(now->snow, x, 6*sizeof(int));
    }
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    // init();
    int tmp[6];
    for (int i=0;i<n;i++){
        for (int j=0;j<6;j++){
            scanf("%d", &tmp[j]);
        }
        int ans = ins(tmp);
        if (ans == -1){
            cout << "Twin snowflakes found." << endl;
            return 0;
        }
    }
    cout << "No two snowflakes are alike." << endl;
    return 0;
}


