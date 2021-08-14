#include <iostream>
#include <set>

using namespace std;

#define MAXN 10000
#define MAXW 10000000

int wall[MAXW];

set<int> s;

// int f(int node )

int count = 1;
int main()
{
    int N;
    cin >> N;

    while (N--){
	int M;
        cin >> M;
	for (int i=0;i<M;i++){
 	    int a, b;
	    cin >> a >> b;
	    for (int j=a;j<=b;j++){
	        wall[j] = count;
	    }
		count++;
	}
	int ans = 0;
    s.clear();    
	for (int i=0;i<MAXW;i++){
	    if (wall[i]>0 ) {
			s.insert(wall[i]);
	    }
	}
    cout << s.size() << endl;

    }
}
