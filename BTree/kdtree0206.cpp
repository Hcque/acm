#include <iostream>
#include <algorithm>
#include <cstring>
#define PA pair<double, KDNode>
#define SQ(x) ((x)*(x))
using namespace std;

const int N = 10e5+10, MAX_D = 2;
int D,n,q, k;

int _size;
struct KDNode{
    int _dim;
    double featrue[MAX_D];
    KDNode()
    {
        memset(flag, 0, sizeof flag);
    }
    inline double SQ_ecu_dist(const KDNode& other) const
    {
        double ans = 0.0;
        for (int i = 0; i < D; i ++ )
        {
            ans += SQ(featrue[i] - other.featrue[i]);
        }
        return ans;
    }

    inline double SQ_dim_dist(const KDNode& other) const
    {
        return SQ(featrue[_size] - other.featrue[_size]);
    }

    bool operator<(const KDNode& other) const
    {
        return featrue[_size] < other.featrue[_size];
    }
};

struct KDTree
{
    KDNode tree[N<<2];
    KDNode data[N];
    priority_queue<PA> que;

    void build(int now, int l , int r, int dep)
    {
        if (l > r) return;
        int mid = l + r >> 1;

        _size = dep % D;
        nth_element(data+l,data+mid, data+r+1);
        tree[now] = data[mid]; tree[now]._dim = _size;
        flag[now] = 1;

        build(l,l,mid-1,dep+1);
        build(r,mid+1,r,dep+1);
    }

    void find_k_c(int now, int k, const KDNode& query)
    {
        _size = query._dim;

        int l = now<<1, r = now<<1|1;
        // determinstic condition
        if (query.SQ_dim_dist(tree[l]) > query.SQ_dim_dist(tree[r]))
            swap(l,r);

        if (flag[l]) find_k_c(l, k, query);

        // main work on this iter
        double _d_ecu = query.SQ_ecu_dist(tree[now]);
        if (que.size() < k )
            que.push();
        else{
            if (que.top().first > _d) que.pop(), que.push({_d, tree[now]});
        }

        if (flag[r])
        {
            if (_d_ecu < que.top().first)
                find_k_c(r, k, query);
        }
    }

};

KDTree kdt;
int main()
{
    while (cin >> n >> D)
    {

        for (int i = 0; i < n; i ++ )
        {
            for (int j = 0; j < D; j ++ )
            {
                cin >> kdt.data[i].featrue[j];
            }
        }
        build(1, 0,n-1,0);
        cin >> q;
        while (q--)
        {
            KDNode query;
            for (int i = 0; i < D; i ++ )
                cin >> query.featrue[i];
            cin >> k;
            while (kdt.que.size()) kdt.que.pop();
            kdt.find_k_c(1, k, query);
#define que kdt.que

            while (que.size())
            {
                auto tmpPA = que.top(); que.pop();
                for (int j = 0; j < D; j ++ )                
                {
                    cout << tmpPA.second.featrue[j] << " ":
                }
                cout << endl;
            }
        }
    }


}