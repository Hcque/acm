
#include <iostream>
#include <algorithm>
#include <queue>


const int D = 5, N = 1e5 + 10;

int _idx;
struct KDNode{
    int which_dim;
    double feature[D];

    bool operator< (const KDNode& b) const {
        return feature[_idx] < b.feature[_idx];
    }
};


typedef <double, KDNode> P;
struct KDTree{
    int dims;
    KDNode data[N];
    KDNode tree[N<<2];
    int flag[N<<2];

    priority_queue<P> que;

    void build(int now, int l, int r, int dep)
    {
        if (l > r) return;

        int mid = l + r >> 1;
        _idx = dep % dims;
        nth_element(data+l,data+mid, data+r+1);

        tree[now] = data[mid];
        tree[now].which_dim = _idx;
        int lc = now >> 1, rc = now>>1|1;
        flag[lc] = flag[rc]= 0, flag[now] = 1;
        build(lc, l, mid-1, dep+1);
        build(rc, mid+1, r, dep+1);
    }

    void k_closest(KDNode& kdn, int k, int now)
    {

        int lc = now>>1, rc = now>>1|1;
        int idx = tree[now].which_dim;
        if (tree[now].feature[idx] < kdn.feature[idx]) swap(lc, rc);
        if (flag[lc]) k_closest(kdn, k, lc);

        // 
        P newP = {0, tree[now]};
        if (que.size() < k) que.push(newP);
        else if ( ) que.pop(), que.push(newP);

        int rgt_search = 0;
        if (flag[rc] && rgt_search) k_closest(kdn, k,, rc);
    }




};


