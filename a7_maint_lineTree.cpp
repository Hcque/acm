//代码长度
// 1.24KB
// 用时
// 677ms
// 内存
// 48.54MB
// https://www.luogu.com.cn/problem/P3834#submit

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 2e5+10;
int a[maxn], n, m;
vector<int> v;
inline int getid(int x){ return lower_bound(v.begin(), v.end(), x)-v.begin()+1; }
struct Node{
    int l, r, sum;
} h[maxn*40];
int root[maxn], cnt;

void insert(int l, int r, int pre, int &now, int p){
    h[now=++cnt] = h[pre];
    h[now].sum++;
    if (l==r) return;
    int m = (l+r)>>1;
    if (p<=m) insert(l,m, h[pre].l, h[now].l, p); 
    else insert(m+1, r, h[pre].r,h[now].r,p);
}

int query(int l,int r, int L, int R, int k){
    if (l==r) return l;
    int m = (l+r)>>1;
    int tmp = h[h[R].l].sum - h[h[L].l].sum;
    if (k<=tmp)return  query(l,m, h[L].l, h[R].l, k);
    else return query(m+1, r, h[L].r, h[R].r,k-tmp);
}

int main(){
    scanf("%d%d", &n,&m);
    for (int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }

    sort(v.begin(),v.end());
    v.erase(std::unique(v.begin(),v.end()), v.end());

    for (int i=1;i<=n;i++)
        insert(1, n, root[i-1], root[i], getid(a[i]));
    int x,y,k;
    while (m--){
        scanf("%d%d%d", &x,&y,&k);
        cout << v[query(1,n,root[x-1], root[y],k)-1] << "\n";
    }


    return 0;
}