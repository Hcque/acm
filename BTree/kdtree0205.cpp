// now not left
// input / output

// new thought of performance issue
// right condition

// build init cond

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

#define SQ(x) ((x)*(x))
#define PA pair<double, KDNode>

using namespace std;
const int N = 1e5+10, D = 2;
int _size;

int n,m, q, M;

struct KDNode
{
    int _dim;
    double featrue[D];
    inline double SQ_dim_Dist(const KDNode& other) const
    {
        return SQ(other.featrue[_size] - featrue[_size]);
    }

    inline double SQ_ecli_Dist(const KDNode& other) const
    {
        double ans;
        for (int i = 0; i < D; i ++ )
        {
            ans += SQ(other.featrue[i] - featrue[i]);
        }
        return ans;
    }

    bool operator< (const KDNode& other) const
    {
        return featrue[_size] < other.featrue[_size];
    }
};

struct KDTree
{
   KDNode data[N] ;
   KDNode tree[N<<2];
   int flag[N<<2];
    priority_queue<PA> que;

   KDTree() 
   {
       memset(flag, 0, sizeof flag);
   }

   void build(int now, int l, int r, int dep)
   {
       if (l > r) return;

       int mid = l+r>>1;
       _size = dep % D; nth_element(data+l, data+mid, data+r+1);
       tree[now] = data[mid]; flag[now] = 1; tree[now]._dim = _size;
       build(now<<1, l,mid-1, dep+1);
       build(now<<1|1, mid+1,r, dep+1);
   }

   void findK_cloest(int now, const KDNode& query, int k)
   {
        if (flag[now] == 0) return;
        // sort, let left cloest
        int l = now<<1, r = now<<1|1;
        _size = tree[now]._dim;

        // if (query.featrue[_size] > tree[now].featrue[_size])
        if ( tree[l].SQ_dim_Dist(query) > tree[r].SQ_dim_Dist(query) )
            swap(l,r);

        double _d = tree[now].SQ_ecli_Dist(query);

        if (que.size() < k) que.push({_d,tree[now]});
        else{
            if (que.top().first > _d)
            {
                que.pop();
                que.push({_d, tree[now]});
            }
        }

        if (flag[l])
            findK_cloest(l, query, k);

        if (flag[r])
        {
            // test
            double _d_query_now = query.SQ_dim_Dist(tree[now]);

            if ( (que.size() >= k && _d_query_now < que.top().first) || que.size() < k)
                findK_cloest(r, query, k);
        }
   }
};

KDTree  kdt;
int main()
{
    while (cin >> n >> M)
    {
        for (int i = 0; i < n ; i ++)
            for (int j = 0; j < M; j ++)
                cin >> kdt.data[i].featrue[j];
        // build the tree
        kdt.build(1, 0, n-1,0);
        
        cin >> q;
        while (q--)
        {
            KDNode query;
            for (int i = 0; i < M; i ++ )            
                cin >> query.featrue[i];
            int k;
            cin >> k;
            // find k cloest
            while (kdt.que.size()) kdt.que.pop();
            kdt.findK_cloest(1, query, k);
#define que kdt.que
            while (que.size())
            {
                auto tmp_d = que.top().first;
                auto tmp_node = que.top().second;
                que.pop();
                for (int i = 0; i < D; i ++ )
                    cout << tmp_node.featrue[i] << " ";
                cout << endl;
            }
        }
    }

}
