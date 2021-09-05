// 1.25KB
// 用时
// 608ms
// 内存
// 50.23MB


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2e6+10;
vector<int> v;
int a[maxn];
struct Node{
    int l,r,cnt;
} h[maxn*40];
int root[maxn], tim=0;

void insert(int l, int r, int pre, int &now, int p){
    h[now=++tim] = h[pre];
    h[now].cnt++;
    if (l==r) return;
    int m = (l+r)>>1;
    if (p<=m) insert(l,m,h[pre].l, h[now].l,p);
    else insert(m+1,r,h[pre].r, h[now].r,p);
}
 int query(int l,int r, int L, int R, int k){
     if (l==r) return l;
     int m = (l+r)>>1;
     int tmp = h[h[R].l].cnt - h[h[L].l].cnt;
     if (k<=tmp) return query(l,m,h[L].l, h[R].l, k);
     else return query(m+1,r, h[L].r, h[R].r, k-tmp);
 }

inline int getid(int x) {
    return 1+lower_bound(v.begin(),v.end(), x)-v.begin();
}

int main(){
    int n,m;
    scanf("%d%d", &n,&m);
    for (int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()),v.end());
    for (int i=1;i<=n;i++) 
        insert(1,n,root[i-1],root[i],getid(a[i]));

    while (m--){
        int l,r,k;
        scanf("%d%d%d", &l,&r,&k);
        printf("%d\n", v[query(1,n,root[l-1],root[r],k)-1] );
    }

    
}