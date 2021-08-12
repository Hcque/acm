#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10005

int p[MAXN], path[MAXN];

int main()
{
    int N, M;
    int a, b;
    cin >> N;
    while (N--)
    {
        fill(path, path+MAXN, 0);
        fill(p, p+MAXN, 0);
        cin >> M;
	for (int i=1;i<M;i++){
	    cin >> a >> b;
	    p[b] = a; 
	}
	cin >> a >> b;
	// cout << a << b;

	while (a!=0) {
	    path[a] = 1;
	    a = p[a];
	}
	// for (int i=0;i<=M;i++) cout<<path[i]<<" "; 
	// cout << endl;
	while (path[b]!=1) {
	    path[b] = 1;
	    b = p[b];
	}
	printf("%d\n", b);
    }
}


