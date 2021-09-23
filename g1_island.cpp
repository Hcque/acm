// poj 1328
// try union find set wrong
// runtine error; break, has input, sqrt continue;
// 316K	47MS


#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn = 1e3+10;
int n;
int d;

struct Interval{
    double l,r;
    // Interval(){}
    Interval(double _l,double _r):l(_l),r(_r){}
    bool operator<(const Interval& b) const { return l<b.l; }
};
vector<Interval> v;
int main(){
    int c = 0;
    while (cin >> n >> d){
        if (n == 0 && d == 0) break;
        v.clear();
        c++;  // init
        int possi=1;
        for (int i=1;i<=n;i++){
            double x, y;
            cin >> x >> y;
            if (d<y) {
                possi=0;
                continue; //!
            }
            double dx = sqrt(d*d - y*y);
            v.push_back (Interval(x-dx, x+dx));
        }
        if (possi==0) {
            printf("Case %d: %d\n", c, -1); 
            continue;
        } 
        sort(v.begin(),v.end());
        double curR = v[0].r; int ans = 1; // first
        for (int i=1;i<n;i++){
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
