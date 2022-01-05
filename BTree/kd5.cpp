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


int main()
{

	cout << que.size() << endl;

}