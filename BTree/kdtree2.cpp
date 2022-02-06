
//4347 1747MS	9752K

// 1716MS	9736K

// pri max

#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

const int N = 1e5+10;
int _idx;

struct KDNode
{
    const static int max_dims = 5;
    double featrue[max_dims];
    int _index;
    int size;
    int region[max_dims][2];
    int dim;
    bool operator<(const KDNode& other) const {
        return featrue[_idx] < other.featrue[_idx];
    }
};
typedef pair<double, KDNode> p;
priority_queue<p> Q;

struct KDTree
{
    int dims;
    KDNode Node[N];
    KDNode data[N<<2];
    int flag[N<<2];

    void build(int o,int l, int r , int dep)
    {
        if (l > r) return;
        _idx = dep%dims;
        int lc = o<<1, rc = o<<1|1;
        flag[o] = 1; flag[lc] = flag[rc] = 0;
        int mid = l + r >> 1;

        nth_element(Node+l,Node+mid,Node+r+1);
        data[o] = Node[mid]; data[o].dim = _idx;
        data[o].size = r-l+1;

        build(lc,l,mid-1, dep+1);
        build(rc,mid+1,r, dep+1);
    }
    void k_close(const KDNode& p, int k, int o)
    {
        int dim = data[o].dim;
        int lc = o<<1, rc = o<<1|1;

        if(p.featrue[dim] > data[o].featrue[dim])swap(lc,rc);

        pair<double,KDNode> cur(0.0,data[o]);
        for (int i = 0; i < dims; i ++ ) 
            cur.first += pow(p.featrue[i]-data[o].featrue[i],2);
        if (flag[lc]) k_close(p,k,lc);
        int fg = 0;
        if (Q.size() < k){
            Q.push(cur); fg = 1;
        }
        else{
            cout << cur.first << " || " <<  Q.top().first << endl;
            if (cur.first < Q.top().first)
            {
                Q.pop(); Q.push(cur);
            }
            fg = pow(p.featrue[dim] - data[o].featrue[dim],2) < Q.top().first;
        }
        if (flag[rc] && fg) k_close(p,k,rc);
    }

};

KDTree kdt;
int main()
{
    int n,k;
    while (scanf("%d%d", &n,&k)!= EOF)
    {
        kdt.dims = k;
        for (size_t i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j ++){
                cin >> kdt.Node[i].featrue[j] ;
            }
            kdt.Node[i]._index = i;
        }
        kdt.build(1,0,n-1,0);
        int m, num;
        cin >> m;
        while (m--){
            KDNode knode;
            for (size_t i = 0; i < k; i++)
                cin >> knode.featrue[i];
            cin >> num;

            while (Q.size()) Q.pop();
            kdt.k_close(knode,  num,1);
            printf("the closest %lf points are:\n",num);
            cout << Q.top().second._index << endl;
        }

    }
}