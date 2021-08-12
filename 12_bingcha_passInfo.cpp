#include <iostream>

using namespace std;
#define MAXN 200005

int n;
int to[MAXN], dist[MAXN], fa[MAXN];


int find(int x){
    if (fa[x] == x) return x;
    return find(fa[x]);
}

int min_dist = INT_MAX;
void Union(int x, int y){
    int a = find(x);
    int b = find(y);

    if (a == b){
    cout << a << endl;
    	if (dist[a] < min_dist) {
            min_dist = dist[a];
            cout << "min" << min_dist << endl;
        }
	return;
    }
    fa[x] = y;
    dist[y]++;
        cout << a << " " << b << " ";
    for (int i=1;i<=n;i++) cout << fa[i] << " ";
    cout << endl;
}

int main()
{
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> to[i];
	dist[i] = 0;
	fa[i] = i;
    }
    for (int i=1;i<=n;i++){
	Union(i,to[i]);
    }
    cout <<  min_dist << endl;
}
