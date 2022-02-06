#include <iostream>
#include <queue>
#include <algorithm>

#define SQ(x) ((x)*(x))
using namespace std;
const int N = 1e5+10;
int _size;

int n,m, q;

struct KDNode
{
    int _dim;
    double featrue[5];
    double SQDist(const KDNode& other)
    {
        return SQ(other.featrue[_size] - featrue[_size]);
    }

    bool operator< (const KDNode& other)
    {
        return featrue[I] < other.featrue[I];
    }
};

struct KDTree
{
   KDNode data[N] ;
   KDNode tree[N<<2];
   int flag[N<<2];

   KDTree() 
   {
       memset(flag, 0, sizeof flag);
   }

   void build(int now, int l, int r, int dep)
   {
       if (l >= r) return;

       int mid = l+r>>1;
       _size = dep % 3; nth_element(data+l, data+mid, data+r+1);
       tree[now] = data[mid]; flag[now] = 1; tree[now]._dim = _size;

       build(now<<1, l,mid-1, dep+1);
       build(now<<1|1, mid+1,r, dep+1);
   }
#define PA pair<double, KDNode>

   void findK_cloest(int now, const KDNode& query, int k)
   {
        priority_queue<PA> que;

        if (flag[now] == 0) return;
        // sort, let left cloest
        int l = now<<1, r = now<<1|1;
        _size = tree[now]._dim;
        if ( tree[l].SQDist(query) > tree[r].SQDist(query) )
            swap(l,r);

        double _d = tree[l].SQDist(query);

        if (que.size() < k) que.push({_d,tree[l]});
        else{
            if (que.top().first > _d)
            {
                que.pop();
                que.push({_d, tree[l]});
            }
        }

        if (flag[l])
            findK_cloest(now<<1, query, k);

        if (flag[r])
        {
            // test
            double _d_right = 0;
            for (int i = 0; i < 3; i ++)
            {
                _d_right += SQ(tree[now].featrue[i] - query.featrue[i]);
            }
            if (_d_right < _d && que.size() < k)
                findK_cloest(now<<1|1, query, k);
        }


   }
};



KDTree  kdt;
int main()
{

    while (cin >> n >> M)
    {
        for (int i = 0; i < n ; i ++)
        {
            for (int j = 0; j < M; j ++)
            {
                cin >> kdt.data[i].featrue[j];
            }
        }
        // build the tree
        kdt.build(1, 0, n-1,0);
        
        cin >> q;
        while (q--)
        {
            for (int i = 0; i < M; i ++ )            
                cin >> query.featrue[i];
            int k;
            cin >> k;
            // find k cloest
            kdt.findK_cloest();

        }
    }

}






