
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int maxn = 1e4+10;
// 海岛在x轴上的投影区间
struct Interval {
	double left,right;
	Interval(double _l , double _r):left(_l), right(_r){}
	bool operator<(const Interval& b) { return left<b.left; }

};
vector<Interval> v;

int solve(vector<Interval>& intervals, int size) {
	sort(intervals.begin(), intervals.end());

	int minPoint = 1;
	double right = intervals[0].right;
	for(int i = 1; i < size; i++) {

		// 区间i-1 与 区间i 无交集
		if(intervals[i].left > right) {
			minPoint++;
			right = intervals[i].right;

		// 区间i-1 在 区间i 内部
		} else if(intervals[i].right < right) {
			right = intervals[i].right;

		} else {
			// Undo: 区间i-1 与 区间i 相交 
		}
	}
	return minPoint;
}

int main(void) {
	int n, d, c = 0;
	while((cin >> n >> d) ) {
		if (n ==0&& d == 0) break;
		v.clear();
		bool isSolvable = true;
		// cout << n;
		for(int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			if(y > d) {	// 存在海岛不在雷达的最大影响范围，无解
				isSolvable = false;
			}

			double dx = sqrt(d*d - y * y);	// 勾股定理
			v.push_back(Interval(x-dx, x+dx));

		}
			if (isSolvable==0){
				cout << "Case " << ++c << ": " << -1 << endl;
				continue;

			}

		int minRadar = (isSolvable ? solve(v, n) : -1);
		cout << "Case " << ++c << ": " << minRadar << endl;
	}
	return 0;
}




