#include <iostream>
#include <queue>
using namespace std;

#define MAXN 20005

int fa[MAXN], enemy[MAXN];

typedef pair<int, int> p;
typedef pair<int,p> pp;
priority_queue<pp,vector<pp>, less<pp> > que;

int find(int x){
    if (fa[x] == x) return x;
    return find(fa[x]);
}

bool union_(int x, int y)
{
    if (find(x) == find(y)) 
        return false;
    if (enemy[x] == 0) 
        enemy[x] = y;
    else 
        fa[enemy[x]] = y;

    if (enemy[y] == 0) 
        enemy[y] = x;
    else 
        fa[enemy[y]] = x; //return false;
    return true;
}

int main()
{
    int N, M;
    cin >> N >> M;
    int a, b, w;
    for (int i=0;i<MAXN;i++){
        fa[i] = i;
        enemy[i] = 0;
    }

    for (int i=0;i<M;i++){
	    cin >> a >> b >> w;
	    que.push(pp(w,p(a,b)));
    }
    pp cur;
    while (1){
        cur = que.top(); que.pop();
        // cout << cur.first << endl;
        int a0 = cur.second.first;
        int b0 = cur.second.second;
        // cout << a0 << " " << b0 << endl;

        // for (int i=1;i<M+1;i++) cout << fa[i] << " ";
        // for (int i=1;i<M+1;i++) cout << enemy[i] << " ";
        bool bb = union_(a0,b0);
        // cout << bb << endl;
    // cout << bb  << cur.first << endl;
        if (! bb){
        // cout << "!" << endl;
	    cout << cur.first << endl;
	    break;
        }
    }


}
