#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2e5+4;
int a[maxn];
vector<int> v;
inline int getid(){}
struct Node{
    int l, r, sum;
} hjt[maxn*40];
int root[maxn], cnt;

void insert(int l, int r, int pre, int now, int p){
    hjt[now=++cnt] = hjt[pre];
    hjt[now].sum++;

    if (l==r) return;
    int m = (l+r)>>1;

}
int main(){
    int n, m;
    for (int i=0;i<n;i++){
        int tmp; cin >> tmp;
        v.push_back( a[i]= tmp);
    }

    sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());





}
}




