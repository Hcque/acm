// char T[N], fill 0 default on main stack
// class operator
///   -- if // wirte wrong next line

// passed 
// 244K	16MS

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 52;
const int M = 102;
int n,m;
class P{
public:
    int first;
    char second[N];
    P(){}
    P(int _i, char* _c):first(_i){
        strcpy(second,_c);
    }
    void operator=(const P& b){
        first = b.first;
        strcpy(second,b.second);
    }
    bool operator<(const P& b)const {
        return first < b.first;
    }
} c[M];
int Sort(const char a[]){
    char tmp[N];
    strcpy(tmp,a);
    int dist = 0;
    for (int i=1;i<n;i++){
        int pos; char cur; 
        if (tmp[i]<tmp[i-1]){
            pos = i; cur = tmp[i];
            do {
                tmp[pos] = tmp[pos-1];
                dist++;
                pos--;
            } while ( pos>0 && tmp[pos-1]>cur);
            tmp[pos] = cur;
        }
    }
    return dist;
}
int main(){
    scanf("%d%d", &n,&m);
    for (int i=1;i<=m;i++){
        scanf("%s", c[i].second);
        c[i].first = Sort(c[i].second);
    }
    // merge sort


    // sort(v.begin(), v.end());
    // insertion
    for (int i=2;i<=m;i++){
        int pos; P cur;
        if (c[i].first < c[i-1].first){
            pos = i;  cur = c[i];
            do{
                c[pos] = c[pos-1];
                pos--;
            } while (pos>1 && c[pos-1].first>cur.first);
            c[pos] = cur;
        }
    }

    for (int i=1;i<=m;i++){
        cout << c[i].second << endl;
    }
}