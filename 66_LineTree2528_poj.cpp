//  Accepted	40000K	922MS

#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <cassert>
using namespace std;

#define MAXN 10001
#define MAXW 10000001

int arr[MAXN][2];
unsigned short wall[MAXW];
unsigned short map_[MAXW];
int pointers[MAXN*2];

set<int> s;

int main()
{
    int N;
    cin >> N;

    while (N--){
		unsigned short cnt = 1;
		s.clear();    
		memset(pointers, 0, MAXN*2*sizeof(int));
		memset(wall, 0, MAXW*sizeof(unsigned short));
		memset(map_, 0, MAXW* sizeof(unsigned short));
		memset(arr, 0, MAXN*2*sizeof(int));
		int M;
        cin >> M;
		int c = 0;
		for (int i=0;i<M;i++){
			int a, b;
			cin >> a >> b;
			arr[i][0] = a;
			arr[i][1] = b;
			if (map_[a] == 0){
				map_[a] = 1;
				pointers[c++] = a;
			}
			if (map_[b] == 0){
				map_[b] = 1;
				pointers[c++] = b;
			}
			// for (int j=a;j<=b;j++){
			//     wall[j] = count;
			// }
			// count++;
		}

		// map n to k;
		sort(pointers, pointers+c);
		unsigned short hash = 0;
		for (int j=0;j<c;j++){
			map_[pointers[j] ] = ++hash;
		}
		// cout << "hash:" << hash << endl;

		for (int i=0;i<M;i++){
			int low,high;
			low = map_[arr[i][0]];
			high = map_[arr[i][1]];
			for (int k=low;k<=high;k++){
				wall[k] = cnt;
			}
			cnt++;
		}

		// for (int i=1;i<=hash;i++){
		// 	cout << wall[i] << " ";
		// }
		// cout << endl;

		int ans = 0;
		for (int i=1;i<=hash;i++){
			if (wall[i]>0 ) {
				s.insert(wall[i]);
			}
		}
		cout << s.size() << endl;
    }
}
