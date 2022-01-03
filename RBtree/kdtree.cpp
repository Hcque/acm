


#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

int n, k;
int m, q;

const int LEN = 5, N = 2e5+10;

struct KDNode
{
    int dim;
    int feature[LEN];
    bool operator<(const KDNode& b) const 
    {
        return feature[dim] < b.feature[dim];
    }
};

struct KDTree
{
    KDNode data[N<<2];
    KDNode post[N<<2];
    int flags[N<<2];

    void build(int now, int l, int r, int dep)
    {
        if (l >= r) return;
        int mid = l+r>>1;
        nth_elements(data+l, data+mid, data+r);

        build(now<<1, l, mid-1,dep+1);
        build(now<<1|1, mid+1, r,dep+1);

    }

    void k_cloest(const KDNode& query, int k)
    {



    }

}
int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < k ; j ++ )
        {
            cin >> data[i][j];
        }
    }

    cin >> m;
    while (m -- )
    {

    }

}