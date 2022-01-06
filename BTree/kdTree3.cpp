
// https://www.shuzhiduo.com/A/nAJvBpe3Jr/

// SQ 
//swap

// build which_dim

// << / >> !!
// SQ (x) !!
// rgt search

#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int D = 5, N = 1e5+10;

int wch_dim;
struct KDNode
{
    int _which_dim;
    double featrue[D];

    bool operator< (const KDNode& b)const
    {
        return featrue[wch_dim] < b.featrue[wch_dim];
    }

};
typedef pair<double, KDNode> P;

priority_queue<P> que;
struct KDTree
{
    int dims;

    KDNode data[N];
    KDNode tree[N<<2];
    int flag[N<<2];
    KDTree(): dims(D)
    {
        memset(flag, 0, sizeof flag);
        
    }

    void build(int now, int l, int r, int dep)
    {
        if (l > r) return;
        int mid = l+r >> 1;
        wch_dim = dep%dims;
        nth_element(data+l,data+mid,data+r+1 );
        tree[now] = data[mid];
        tree[now]._which_dim = wch_dim;

        int lc = now<<1, rc = now<<1|1;
        flag[lc] = flag[rc] = 0; flag[now] = 1;
        build(lc, l, mid-1, dep+1);
        build(rc, mid+1, r, dep+1);
    }


#define SQ(x) ((x)*(x))

   void k_close(const KDNode& p, int k, int o)
    {
        int dim = tree[o]._which_dim;
        int lc = o<<1, rc = o<<1|1;

        if(p.featrue[dim] > data[o].featrue[dim])swap(lc,rc);

        pair<double,KDNode> cur(0.0,tree[o]);
        for (int i = 0; i < dims; i ++ ) 
            cur.first += SQ(p.featrue[i]-tree[o].featrue[i]);
        if (flag[lc]) k_close(p,k,lc);
        int fg = 0;
        if (que.size() < k){
            que.push(cur); fg = 1;
        }
        else{
            cout << cur.first << " || " <<  que.top().first << endl;
            if (cur.first < que.top().first)
            {
                que.pop(); que.push(cur);
            }
            fg = SQ(p.featrue[dim] - tree[o].featrue[dim]) < que.top().first;
        }
        if (flag[rc] && fg) k_close(p,k,rc);
    }


    void find_k_cloest(KDNode& kdnode, int now, int k)
    {

        int lc = now<<1, rc = now<<1|1;
        int which_dim = tree[now]._which_dim;
        if (tree[now].featrue[which_dim] < kdnode.featrue[which_dim] )
        {
            swap(lc, rc);
        }

        P p = {0.0,tree[now]}; // !!!
        for (int i = 0; i < dims; i ++ )
            p.first += SQ(kdnode.featrue[i] - tree[now].featrue[i]);
        if (flag[lc]) find_k_cloest(kdnode, lc, k);

        int rgt_search = 0;
        if (que.size() < k) que.push(p), rgt_search = 1;
        else if ( que.top().first > p.first) 
        {
            que.pop();
            que.push(p);
            rgt_search =  que.top().first > SQ(tree[now].featrue[which_dim] - kdnode.featrue[which_dim]);
        }

        // rgt_search = (que.size() <= k) || ( que.top().first > SQ(tree[rc].featrue[which_dim] - kdnode.featrue[which_dim]) );

        if (flag[rc] && rgt_search) find_k_cloest(kdnode, rc, k);

    }

};

int n,m;

KDTree kdt;
int main()
{

    cin >> n >> m;
    kdt.dims = m;

    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < m; j ++ )
        {
            cin >> kdt.data[i].featrue[j];
        }
    }
    kdt.build(1, 0,n-1,0);

    int q, k;
    cin >> q;
    // cout << "q" << q<< endl;
    while (q--)
    {
        KDNode kdn;
        for (int i = 0; i < m; i ++ )
        {
            cin >> kdn.featrue[i];
        }

        cin >> k;
        // cout << "k" << k << endl;
        while (que.size()) 
            que.pop();
        // kdt.k_close(kdn,  k, 1);
        kdt.find_k_cloest(kdn, 1, k);
        printf("the closest %d points are:\n", k );
        vector<KDNode> tmpvec;
        for (int i = 0; i < k; i ++ )
        {
            tmpvec.push_back(que.top().second);
            que.pop();
        }

        for (int i= k-1;i>= 0; i --) {
            for (int j = 0;j < kdt.dims; j ++ )
                cout << tmpvec[i].featrue[j] << " ";
            cout << endl;
        }
    }


}




