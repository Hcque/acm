// poj 1328
// try union find set wrong
// runtine error;


#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int maxn = 1e5+10;
int n;
int d;

struct Interval{
    double l,r;
    Interval(){}
    Interval(double _l,double _r):l(_l),r(_r){}
    bool operator<(const Interval& b) const { return l<b.l; }
};
vector<Interval> v;
int main(){
    int c = 0;
    while (cin >> n >> d){
        if (n == 0 && d == 0) break;
        v.clear(); c++;  // init
        int possi=1;
        for (int i=1;i<=n;i++){
            double x, y;
            cin >> x >> y;
            if (d<y) {
                possi=0;
                break;
            }
            double dx = sqrt(d*d - y*y);
            v.push_back(Interval(x-dx, x+dx));
        }
        if (possi==0) {
            printf("Case %d: %d\n", c, -1); continue;
        }
        //
        sort(v.begin(), v.end());
        double curR = v[0].r; int ans = 1; // first
        for (int i=1;i<v.size();i++){
            if (v[i].l > curR){
                ans++;
                curR = v[i].r;
            }
            else if (v[i].r < curR){
                curR = v[i].r;
            }
        }
        printf("Case %d: %d\n", c, ans);
    }
}

/*
void init(){
    for (int i=1;i<=n;i++) fa[i] = i;
}

int Find(int x){
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}
int Same(int x, int y){ return Find(x) == Find(y); }
void Union(int p1, int p2){
    double x1 = l[p1], y1 = r[p1];
    double x2 = l[p2], y2 = r[p2];
    if (x1 > y2 || y1 < x2) return;
    int u = Find(p1), v = Find(p2);
    if (u==v) return;
    else {
        fa[u] = v;
    }
}
*/