#include <iostream>
using namespace std;

#define MAXN 10000

int fa[MAXN], dist[MAXN], enemy[MAXN];

int find(int x){
    if (fa[x] == x) return x;
    return find(fa[x]);
}
void unionAll(int x, int y)
{
    int a = find(x);
    int b = find(y);
    if (a != b) fa[a] = b;
}

int main()
{
    int N, M;
    cin >> N >> M;

    for (int i=1;i<=N;i++){
        fa[i] = i;
	enemy[i] = 0;
    }
    char ef;
    int a, b;
    for (int i=0;i<M;i++){
        cin >> ef >> a >> b;
	switch (ef){
	    case 'F': unionAll(a, b); break;
	    case 'E':
	    	if (enemy[a] == 0) enemy[a] = b;
		else unionAll(enemy[a],b);
	    	if (enemy[b] == 0) enemy[b] = a;
		else unionAll(enemy[b],a);
		break;
	}

    }

    int cnt = 0;
    for (int i=1;i<=N;i++)
    	if (fa[i]==i) cnt++;
    cout << cnt << endl;
    return 0;
}


