#include <iostream>
using namespace std;

const int maxn = 1e5+4;
struct Node{
    int l, r;
    int val, key, size;
} T[maxn];
int cnt, root;

#include <random>
std::mt19937 rnd(233);
inline int  newNode(int val){
    T[++cnt].val = val;
    T[cnt].key = rnd();
    T[cnt].size = 1;
    return cnt;
}
inline void update(int now){
    T[now].size = T[ T[now].l].size + T[T[now].r].size + 1;
}
void split(int now, int val, int& x, int &y){
    if (!now) x = y = 0;
    else {
        if (T[now].val <= val){
	    x = now;
	    split(T[now].r, val, T[now].r, y);
	} else {
	    y = now;
	    split(T[now].l, val, x, T[now].l);
	}
	update(now);
    }
}

int merge(int x, int y){
    if (!x || !y) return x+y;
    if (T[x].key>T[y].key){
        T[x].r = merge(T[x].r, y);
	update(x);
	return x;
    }
    else {
        T[y].l = merge(x, T[y].l);
	update(y);
	return y;
    }
}
int x, y, z;
inline void insert(int val){
    split(root, val, x, y);
    root = merge(merge(x, newNode(val)), y);
}

void del(int val){
    split(root, val, x, z);
    split(x, val-1, x, y);
    y = merge(T[y].l, T[y].r);
    root = merge(merge(x,y), z);
}

inline void getrank(int val){
    split(root, val-1, x, y);
    cout << T[x].size + 1 << endl;
    root = merge(x,y);
}


inline void getnum(int rank)
{
    int now=root;
    while(now)
    {
        if(T[T[now].l].size+1==rank)
            break;
        else if(T[T[now].l].size>=rank)
            now=T[now].l;
        else 
        {
            rank-=T[T[now].l].size+1;
            now=T[now].r;
        }
    }
    cout << (T[now].val) << endl;
}
/*
inline void getnum(int rank){
    int now = root;
    while (now) {
        if (T[T[now].l].size + 1 == rank ) 
            break;
        else if (T[T[now].l].size >= rank) 
                now = T[now].l;
        else{
                rank -= T[T[now].l].size + 1;
                now = T[now].r;
            }
    }
    cout << T[now].val << endl;
}
*/
inline void pre(int val){
    split(root, val-1, x, y);
    int now = x;
    while (T[now].r){
        now = T[now].r;
    }
    cout << T[now].val << endl;
    root = merge(x, y);
}

inline void post(int val){
    split(root, val, x, y);
    int now = y;
    while (T[now].l) {
        now = T[now].l;
    }
    cout << T[now].val << endl;
    root = merge(x, y);
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int op, x;
	cin >> op >> x;
	switch (op){

	case 1: insert(x); break;
	case 2: del(x); break;
	case 3: 
	     getrank(x);
	    break;
	case 4: 
	    getnum(x);
	    break;
	case 5: 
	    pre(x);
	    break;
	case 6: 
	    post(x);
	    break;
    }
    }
}

