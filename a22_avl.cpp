// !l!r

// hei / siz 
// now pass by ref
// fa.l = now.r;
// find ret

#include <iostream>
using namespace std;

const int maxn = 1e5+4;
struct Node{
    int l,r,size,heig, val;
    Node(){}
    Node(int _v): val(_v), l(0), r(0), heig(0), size(0){}
} avl[maxn];
int root, cnt=0;

void newNode(int& now, int val){
    avl[now=++cnt].val=val;
    avl[cnt].size = 1;
}

void update(int now){
    avl[now].heig = 1+ std::max(avl[avl[now].l].heig, avl[avl[now].r].heig);
    avl[now].size = 1+ avl[avl[now].l].size + avl[avl[now].r].size;
}

void lrotate(int &now){
    int r = avl[now].r;
    avl[now].r = avl[r].l;
    avl[r].l = now;
    now = r;
    update(avl[now].l); update(now);
}
void rrotate(int &now){
    int l = avl[now].l;
    avl[now].l = avl[l].r;
    avl[l].r = now;
    now = l;
    update(avl[now].r); update(now);
}
inline int factor(int now){
    return  avl[avl[now].l].heig - avl[avl[now].r].heig;
}


void check(int &now){
    if (!now) return;
    if (factor(now)>1){
        if (factor(avl[now].l)>=0)
             rrotate(now);
        else { lrotate(avl[now].l); rrotate(now); }
    }
    else if (factor(now)<-1){
        if (factor(avl[now].r)<=0)
             lrotate(now);
        else { rrotate(avl[now].r); lrotate(now); }
    }
    update(now);
}
void insert(int &now, int val){
    if (!now){ newNode(now, val); }
    else if (val < avl[now].val) insert(avl[now].l, val);
    else insert(avl[now].r, val);
    check(now);
}

int find(int &now, int fa){
    int ret;
    if (!avl[now].l) {
        ret = now;
        avl[fa].l=avl[now].r;
    }
    else {
        ret = find(avl[now].l, now);
        check(now);
    }
    return ret;
}

// int find(int &now, int fa){
//     int ret;
//     if (!avl[now].l){
//         ret = now;
//         avl[fa].l = avl[now].r;
//     }
//     else {
//         ret = find(avl[now].l, now);
//         check(now);
//     }
//     return ret;
// }

void del(int &now, int val){
    if (val == avl[now].val){
        // del_node(now);
        int l = avl[now].l, r = avl[now].r;
        if (!l||!r) now = l+r;
        else {
            now = find(r,r);
            if (now != r){
                avl[now].r = r;
            }
            avl[now].l = l;
        }
    }
    else if (val < avl[now].val) del(avl[now].l, val);
    else del(avl[now].r, val);
    check(now);

   
}



int getrank(int val){
    int now = root, rank = 1;
    while (now){
        if (val <= avl[now].val)
            now = avl[now].l;
        else {
            rank += avl[avl[now].l].size + 1;
            now = avl[now].r;
        }
    }
    return rank;
}
int getnum(int rank){
    int now = root;
    while (now){
        if (avl[avl[now].l].size+1==rank)
            break;
        if (avl[avl[now].l].size >= rank)
            now = avl[now].l;
        else {
            rank -= avl[avl[now].l].size+1;
            now = avl[now].r;
        }
    }
    return avl[now].val;
}

int main(){
    int T;
    cin >> T;
    while (T--){
        int op, x;
	cin >> op >> x;
    // cout << op << endl;
	switch (op){
	    case 1: insert(root, x); break;
	    case 2: del(root, x); break;
	    case 3: cout << getrank(x) << endl; break;
	    case 4: cout << getnum(x) << endl; break;
	    case 5: cout << getnum(getrank(x)-1) << endl; break;
	    case 6: cout << getnum(getrank(x+1)) << endl; break;
	}
    }

}


